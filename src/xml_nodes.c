/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:01:40 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/23 16:43:03 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				xml_node_scene(t_env *e, char *node, char mod)
{
	if (mod == 0)
	{
		if (ft_strlen(node) != 7)
			s_error("\x1b[2;31mError in XML syntax\x1b[0m", e);
		XML->in_scene = 1;
	}
	else if (mod == 1)
	{
		if (ft_strlen(node) != 8)
			s_error("\x1b[2;31mError in XML syntax\x1b[0m", e);
		XML->in_scene = 0;
	}
}

void				xml_node_generic(t_env *e, char *node, char mod)
{
	if (mod == 0)
	{
		if (ft_strcmp(node, "?xml version=\"1.0\"?> ") != 0)
			s_error("\x1b[2;31mError XML header is invalid\x1b[0m", e);
	}
	else if (mod == 1)
	{
		if ((node = ft_strstr(node, "-->")) != NULL)
		{
			XML->is_comm = 0;
			if (ft_strlen(node) != 4)
				s_error("\x1b[2;31mError in XML syntax\x1b[0m", e);
		}
		else
			XML->is_comm = 1;
	}
}

void				xml_process_node(t_env *e, char *node)
{
	XML->sub_node = ft_strsplit(node, ' ');
//	printf("node is %s\n", XML->sub_node[0]);
	if (ft_strcmp(XML->sub_node[0], "!--") == 0 ||  XML->is_comm == 1)
		xml_node_generic(e, node, 1);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "?xml") == 0)
		s_error("\x1b[2;31mError double XML header\x1b[0m", e);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "scene>") == 0)
		xml_node_scene(e, node, 0);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "/scene>") == 0)
		xml_node_scene(e, node, 1);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "cam") == 0)
		xml_node_cam(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "cone") == 0)
		xml_node_cone(e, node);	
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "cylinder") == 0)
		xml_node_cylinder(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "light") == 0)
		xml_node_light(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "plane") == 0)
		xml_node_plane(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "sphere") == 0)
		xml_node_sphere(e, node);
	else
		s_error("\x1b[2;31mError wrong node type\x1b[0m", e);
	xml_node_clean(XML->sub_node);
}

void				xml_parse_nodes(t_env *e)
{
	int				i;

	i = 0;
	if ((XML->nodes = ft_strsplit(XML->scene, '<')) == NULL)
		s_error("\x1b[2;31mError getting nodes\x1b[0m", e);
	while (XML->nodes[i])
	{
//		ft_putendl(XML->nodes[i]);
		if (i == 0)
			xml_node_generic(e, XML->nodes[i], 0);
		else
			xml_process_node(e, XML->nodes[i]);
		i++;
	}
//	xml_node_clean(XML->nodes);  USELESS
}
