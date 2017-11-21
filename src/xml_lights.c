/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:58 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/21 16:01:22 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	xml_light_data(t_env *e, char **att, t_node *light_node, int *i)
{
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[2;31mError in light, ID expected in #0\x1b[0m", e);
	else
		light_node->id = ft_atoi(att[(*i)++] + 4);
	printf("light id = %d\n", light_node->id);
	if (ft_strncmp(att[*i], "type=\"", 6) != 0)
		s_error("\x1b[2;31mError in light, TYPE expected in #1\x1b[0m", e);
	else
		xml_data_type(e, att, i, light_node);
	printf("type = %d\n", light_node->type);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[2;31mError in light, POS expected in #2\x1b[0m", e);
	else
		xml_data_pos(e, att, i, light_node);
	printf("pos x = %f | y = %f | z = %f\n", light_node->pos.x, light_node->pos.y, light_node->pos.z);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[2;31mError in light, DIR expected in #3\x1b[0m", e);
	else
		xml_data_dir(e, att, i, light_node);
	printf("dir x = %f | y = %f | z = %f\n", light_node->dir.x, light_node->dir.y, light_node->dir.z);
	if (ft_strncmp(att[*i], "intensity=\"",	11) != 0)
		s_error("\x1b[2;31mError in light, INTENSITY expected in #4\x1b[0m", e);
	else
		xml_data_intens(e, att, i, light_node);
	printf("angle = %f\n", light_node->intensity);
	if (ft_strncmp(att[*i], "color=\"", 7) != 0)
		s_error("\x1b[2;31mError in light, COLOR expected in #5\x1b[0m", e);
	else
		xml_data_color(e, att, i, light_node);
	printf("color = %d\n", light_node->color);
}

void		xml_node_light(t_env *e, char *node)
{
	t_node	*light_node;
	char	**tmp;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	light_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_light_data(e, tmp, light_node, &i);	
	if (XML->node_lst == NULL)
		XML->node_lst = light_node;
	else
		xml_list_add_first(&XML->node_lst, light_node);
	xml_node_clean(tmp);
	NLIG++;
}
