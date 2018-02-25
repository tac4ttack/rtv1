/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:01:40 by fmessina          #+#    #+#             */
/*   Updated: 2018/02/25 14:38:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					xml_check_node_format(char **node, int mod)
{
	cl_int2				i;
	
	i.x = 0;
	i.y = 0;
	if (node)
	{
		i.y = (mod == 0 ? i.y = 6 : i.y);
		i.y = (mod == 1 ? i.y = 10 : i.y);
		i.y = (mod == 2 ? i.y = 21 : i.y);
		i.y = (mod == 3 ? i.y = 22 : i.y);
		i.y = (mod == 4 ? i.y = 16 : i.y);
		i.y = (mod == 5 ? i.y = 20 : i.y);
		i.y = (mod == 6 ? i.y = 21 : i.y);
		while (i.x <= i.y)
		{
			if (i.x == i.y && node[i.x] != NULL)
				return (1);
			else
				if (i.x < i.y && node[i.x] == NULL)
					return (1);
			i.x++;
		}
		return (0);
	}
	return (1);
}

void				xml_node_generic(t_env *e, char *node, char mod)
{
	char			*tmp;

	tmp = ft_strtrim(node);
	if (mod == 0)
	{
		if (ft_strcmp(tmp, "?xml version=\"1.0\"?>") != 0)
			s_error("\x1b[2;31mError XML header is invalid\x1b[0m", e);
	}
	else if (mod == 1)
	{
		if ((node = ft_strstr(tmp, "-->")) != NULL)
		{
			XML->is_comm = 0;
			if (ft_strlen(node) != 3)
			{
				ft_putstr("\x1b[2;31mWRONG NODE = \x1b[0m");
				ft_putstr(node);
				s_error("\x1b[2;31mError in XML syntax\x1b[0m", e);
			}
		}
		else
			XML->is_comm = 1;
	}
	free(tmp);
}

void				xml_process_node(t_env *e, char *node)
{
	XML->sub_node = ft_strsplit(node, ' ');
	if (xml_check_attr(XML->sub_node) != 0)
	{
		printf("\x1b[2;31mError in node %s\x1b[0m", XML->sub_node[0]);
		exit(0);
	}
	if (ft_strcmp(XML->sub_node[0], "!--") == 0 || XML->is_comm == 1)
		xml_node_generic(e, node, 1);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "?xml") == 0)
		s_error("\x1b[2;31mError double XML header\x1b[0m", e);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "scene") == 0)
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
		if (i == 0)
			xml_node_generic(e, XML->nodes[i], 0);
		else
			xml_process_node(e, XML->nodes[i]);
		i++;
	}
}
