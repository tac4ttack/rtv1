/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_planes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:46 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/25 15:26:38 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	xml_plane_data(t_env *e, char **att, t_node *plane_node, int *i)
{
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[2;31mError in plane, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != NPLA - 1)
		s_error("\x1b[2;31mError in plane, ID is incorrect\x1b[0m", e);
	else
		plane_node->id = ft_atoi(att[(*i)++] + 4);
	printf("\nPLANE id = %d\n", plane_node->id);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[2;31mError in plane, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, plane_node);
	printf("pos x = %f | y = %f | z = %f\n", plane_node->pos.x, plane_node->pos.y, plane_node->pos.z);
	if (ft_strncmp(att[*i], "normale=\"", 9) != 0)
		s_error("\x1b[2;31mError in plane, NORMALE expected in #2\x1b[0m", e);
	else
		xml_data_normale(e, att, i, plane_node);
	printf("normale x = %f | y = %f | z = %f\n", plane_node->normale.x, plane_node->normale.y, plane_node->normale.z);
	if (ft_strncmp(att[*i], "color=\"",	7) != 0)
		s_error("\x1b[2;31mError in plane, COLOR expected in #3\x1b[0m", e);
	else
		xml_data_color(e, att, i, plane_node);
	printf("color = %xd\n", plane_node->color);
}

void		xml_node_plane(t_env *e, char *node)
{
	t_node	*plane_node;
	char	**tmp;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	NPLA++;
	plane_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_plane_data(e, tmp, plane_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[2;31mError PLANE node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[2;31mError PLANE node isn't closed\x1b[0m", e);
	plane_node->type = 4;
	if (XML->node_lst == NULL)
		XML->node_lst = plane_node;
	else
		xml_list_add_first(&XML->node_lst, plane_node);
	xml_node_clean(tmp);
}

void		xml_allocate_plane(t_env *e)
{
	if (NPLA > 0)
	{
		if (!(e->planes = malloc(sizeof(t_plane) * NPLA)))
			s_error("\x1b[2;31mCan't create planes array\x1b[0m", e);
	}
	else
		e->planes = NULL;
}

void		xml_push_plane(t_env *e, t_node *list)
{
	e->planes[list->id].pos = list->pos;
	e->planes[list->id].normale = list->normale;
	e->planes[list->id].color = list->color;
}
