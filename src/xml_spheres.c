/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:26 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/25 15:26:46 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	xml_sphere_data(t_env *e, char **att, t_node *sphere_node, int *i)
{
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[2;31mError in sphere, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != NSPH - 1)
		s_error("\x1b[2;31mError in sphere, ID is incorrect\x1b[0m", e);
	else
		sphere_node->id = ft_atoi(att[(*i)++] + 4);
	printf("\nSPHERE id = %d\n", sphere_node->id);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[2;31mError in sphere, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, sphere_node);
	printf("pos x = %f | y = %f | z = %f\n", sphere_node->pos.x, sphere_node->pos.y, sphere_node->pos.z);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[2;31mError in sphere, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, sphere_node);
	printf("dir x = %f | y = %f | z = %f\n", sphere_node->dir.x, sphere_node->dir.y, sphere_node->dir.z);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[2;31mError in sphere, RADIUS expected in #3\x1b[0m", e);
	else
		xml_data_radius(e, att, i, sphere_node);
	printf("radius = %f\n", sphere_node->radius);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[2;31mError in sphere, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, sphere_node);
	printf("color = %xd\n", sphere_node->color);
}

void		xml_node_sphere(t_env *e, char *node)
{
	t_node	*sphere_node;
	char	**tmp;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	NSPH++;
	sphere_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_sphere_data(e, tmp, sphere_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[2;31mError SPHERE node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[2;31mError SPHERE node isn't closed\x1b[0m", e);
	sphere_node->type = 5;
	if (XML->node_lst == NULL)
		XML->node_lst = sphere_node;
	else
		xml_list_add_first(&XML->node_lst, sphere_node);
	xml_node_clean(tmp);
}

void		xml_allocate_sphere(t_env *e)
{
	if (NSPH > 0)
	{
		if (!(e->spheres = malloc(sizeof(t_sphere) * NSPH)))
			s_error("\x1b[2;31mCan't create spheres array\x1b[0m", e);
	}
	else
		e->spheres = NULL;
}

void		xml_push_sphere(t_env *e, t_node *list)
{
	e->spheres[list->id].pos = list->pos;
	e->spheres[list->id].dir = list->dir;
	e->spheres[list->id].radius = list->radius;
	e->spheres[list->id].color = list->color;
}