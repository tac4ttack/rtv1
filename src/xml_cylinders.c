/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cylinders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:18 by fmessina          #+#    #+#             */
/*   Updated: 2017/12/11 13:58:26 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	xml_cylinder_data_n(t_env *e, char **att, t_node *cyl_node, int *i)
{
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[2;31mError in cylinder, COLOR expected in #4\x1b[0m", e);
	else
		xml_data_color(e, att, i, cyl_node);
	printf("color= %xd\n", cyl_node->color);
	if (ft_strncmp(att[*i], "height=\"", 8) != 0)
		s_error("\x1b[2;31mError in cylinder, HEIGHT expected in #5\x1b[0m", e);
	else
		xml_data_height(e, att, i, cyl_node);
	printf("height= %lf\n", cyl_node->height);
	if (ft_strncmp(att[*i], "diff=\"", 6) != 0)
		s_error("\x1b[2;31mError in cylinder, \
				DIFFUSE expected in #5\x1b[0m", e);
	else
		xml_data_diffiouse(e, att, i, cyl_node);
	printf("diff.x = %f | diff.y = %f | diff.z = %f\n", cyl_node->diff.x, cyl_node->diff.y, cyl_node->diff.z);
	if (ft_strncmp(att[*i], "spec=\"", 6) != 0)
		s_error("\x1b[2;31mError in cylinder, \
				SPECULAR expected in #6\x1b[0m", e);
	else
		xml_data_speculos(e, att, i, cyl_node);
	printf("spec.x = %f | spec.y = %f | spec.z = %f\n", cyl_node->spec.x, cyl_node->spec.y , cyl_node->spec.z);}

static void	xml_cylinder_data(t_env *e, char **att, t_node *cyl_node, int *i)
{
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[2;31mError in cylinder, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != NCYL - 1)
		s_error("\x1b[2;31mError in cylinder, ID is incorrect\x1b[0m", e);
	else
		cyl_node->id = ft_atoi(att[(*i)++] + 4);
	printf("\nCYLINDER id = %d\n", cyl_node->id);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[2;31mError in cylinder, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cyl_node);
	printf("pos x = %f | y = %f | z = %f\n", cyl_node->pos.x, cyl_node->pos.y, cyl_node->pos.z);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[2;31mError in cylinder, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cyl_node);
	printf("dir x = %f | y = %f | z = %f\n", cyl_node->dir.x, cyl_node->dir.y, cyl_node->dir.z);
	if (ft_strncmp(att[*i], "radius=\"", 8) != 0)
		s_error("\x1b[2;31mError in cylinder, RADIUS expected in #3\x1b[0m", e);
	else
		xml_data_radius(e, att, i, cyl_node);
	printf("radius = %f\n", cyl_node->radius);
	xml_cylinder_data_n(e, att, cyl_node, i);
}

void		xml_node_cylinder(t_env *e, char *node)
{
	t_node	*cyl_node;
	char	**tmp;
	int		i;

	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	NCYL++;
	cyl_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_cylinder_data(e, tmp, cyl_node, &i);
	if (tmp[i] == NULL)
	{
		if (ft_strstr(tmp[i - 1], "/>") == NULL)
			s_error("\x1b[2;31mError CYLINDER node isn't closed\x1b[0m", e);
	}
	else if (ft_strcmp(tmp[i], "/>") != 0)
		s_error("\x1b[2;31mError CYLINDER node isn't closed\x1b[0m", e);
	cyl_node->type = 2;
	if (XML->node_lst == NULL)
		XML->node_lst = cyl_node;
	else
		xml_list_add_first(&XML->node_lst, cyl_node);
	xml_node_clean(tmp);
}

void		xml_allocate_cyl(t_env *e)
{
	if (NCYL > 0)
	{
		if (!(e->cylinders = malloc(sizeof(t_cylinder) * NCYL)))
			s_error("\x1b[2;31mCan't create cylinders array\x1b[0m", e);
	}
	else
		e->cylinders = NULL;
}

void		xml_push_cyl(t_env *e, t_node *list)
{
	e->cylinders[list->id].pos = list->pos;
	e->cylinders[list->id].base_dir = list->dir;
	e->cylinders[list->id].dir = list->dir;
	e->cylinders[list->id].radius = list->radius;
	e->cylinders[list->id].color = list->color;
	e->cylinders[list->id].height = list->height;
	e->cylinders[list->id].diff = list->diff;
	e->cylinders[list->id].spec = list->spec;
}
