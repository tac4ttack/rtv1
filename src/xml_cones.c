/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cones.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:38 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/25 15:26:11 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	xml_cone_data(t_env *e, char **att, t_node *cone_node, int *i)
{
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[2;31mError in cone, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != NCON - 1)
		s_error("\x1b[2;31mError in cone, ID is incorrect\x1b[0m", e);
	else
		cone_node->id = ft_atoi(att[(*i)++] + 4);
	printf("\nCONE id = %d\n", cone_node->id);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[2;31mError in cone, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cone_node);
	printf("pos x = %f | y = %f | z = %f\n", cone_node->pos.x, cone_node->pos.y, cone_node->pos.z);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[2;31mError in cone, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cone_node);
	printf("dir x = %f | y = %f | z = %f\n", cone_node->dir.x, cone_node->dir.y, cone_node->dir.z);
	if (ft_strncmp(att[*i], "angle=\"",	7) != 0)
		s_error("\x1b[2;31mError in cone, ANGLE expected in #3\x1b[0m", e);
	else
		xml_data_angle(e, att, i, cone_node);
	printf("angle = %f\n", cone_node->angle);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[2;31mError in cone, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, cone_node);
	printf("color = %xwd\n", cone_node->color);
}

void		xml_node_cone(t_env *e, char *node)
{
	t_node	*cone_node;
	char	**tmp;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	NCON++;
	cone_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_cone_data(e, tmp, cone_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[2;31mError CONES node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[2;31mError CONES node isn't closed\x1b[0m", e);
	cone_node->type = 1;
	if (XML->node_lst == NULL)
		XML->node_lst = cone_node;
	else
		xml_list_add_first(&XML->node_lst, cone_node);
	xml_node_clean(tmp);
}

void		xml_allocate_cone(t_env *e)
{
	if (NCON > 0)
	{
		if (!(e->cones = malloc(sizeof(t_cone) * NCON)))
			s_error("\x1b[2;31mCan't create cones array\x1b[0m", e);
	}
	else
		e->cones = NULL;
}

void		xml_push_cone(t_env *e, t_node *list)
{
	e->cones[list->id].pos = list->pos;
	e->cones[list->id].dir = list->dir;
	e->cones[list->id].angle = list->angle;
	e->cones[list->id].color = list->color;
}