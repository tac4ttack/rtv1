/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:01:40 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/17 18:48:10 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// fonction de controle des resultat pour des tests
void		print_nodes(t_env *e, char **nodes)
{
	int	i = 0;
	while (i < XML->lbra)
	{
		// test en dessous fonctionne, peut servir a clean les comments
		if (i == 1)
		{
			char *test = ft_strstr(nodes[i], "cul");
			test++;
			test++;
			if (*test == nodes[i][6])
				printf("%c | %c\n", *test, nodes[i][6]);
		}
		printf("%s\n", nodes[i]);
		i++;
	}
}

void				xml_node_comment(t_env *e, char *node)
{
	XML->is_comm = ft_strlen(node);
	ft_putstr("it's a comment!\n\n");
	XML->is_comm = 0;	
}

static 	void		xml_check_header(t_env *e, char *node)
{
	if (ft_strcmp(node, "?xml version=\"1.0\" encoding=\"UTF-8\"?> ") != 0)
		s_error("\x1b[2;31mError XML header is invalid\x1b[0m", e);
}

void				xml_process_node(t_env *e, char *node)
{
	XML->sub_node = ft_strsplitcount(node, ' ', &XML->n_sub);
	if (ft_strcmp(XML->sub_node[0], "!--") == 0)
		xml_node_comment(e, node);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "?xml") == 0)
		s_error("\x1b[2;31mError double XML header\x1b[0m", e);
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "scene>") == 0)
		ft_putstr("it's a scene!\n\n");
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "/scene>") == 0)
		ft_putstr("it's a end of scene!\n\n");
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "cam") == 0)
		ft_putstr("it's a camera!\n\n");
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "cone") == 0)
		ft_putstr("it's a cone!\n\n");
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "cylinder") == 0)
		ft_putstr("it's a cylinder!\n\n");
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "light") == 0)
		ft_putstr("it's a light!\n\n");
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "plane") == 0)
		ft_putstr("it's a plane!\n\n");
	else if (XML->is_comm == 0 && ft_strcmp(XML->sub_node[0], "sphere") == 0)
		ft_putstr("it's a sphere!\n\n");
	else
		s_error("\x1b[2;31mError wrong node type\x1b[0m", e);
	//free sub node
	xml_node_clean(XML->sub_node, XML->n_sub);
}

void				xml_parse_nodes(t_env *e)
{
	int				i;

	i = 0;
	if ((XML->nodes = ft_strsplitcount(XML->scene, '<', &XML->n_nodes)) == NULL)
		s_error("\x1b[2;31mError getting nodes\x1b[0m", e);
	while (i < XML->n_nodes)
	{
		ft_putendl(XML->nodes[i]);
		if (i == 0)
			xml_check_header(e, XML->nodes[i]);
		else
			xml_process_node(e, XML->nodes[i]);
		i++;
	}
//	xml_node_clean(XML->nodes, XML->n_nodes);
}
