/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cylinders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:18 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/20 17:37:14 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	xml_node_cylinder(t_env *e, char *node)
{
	t_node	*cyl_node;
	char	**tmp;
	char	*cursor;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	cyl_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	if ((cursor = ft_strstr(tmp[i], "id=\"")) == NULL)
		s_error("\x1b[2;31mError in cylinder, ID expected in #0\x1b[0m", e);
	else
	{
		cyl_node->id = ft_atoi(cursor + 4);
		i++;
	}
	printf("CYLINDER id = %d\n", cyl_node->id);
	if ((cursor = ft_strstr(tmp[i], "pos=\"")) == NULL)
		s_error("\x1b[2;31mError in cylinder, POS expected in #1\x1b[0m", e);
	else
	{
		cyl_node->pos.x = atof(cursor + 5);
		cyl_node->pos.y = atof(tmp[i + 1]);
		cyl_node->pos.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("pos x = %f | y = %f | z = %f\n", cyl_node->pos.x, cyl_node->pos.y, cyl_node->pos.z);
	if ((cursor = ft_strstr(tmp[i], "dir=\"")) == NULL)
		s_error("\x1b[2;31mError in cylinder, DIR expected in #2\x1b[0m", e);
	else
	{
		cyl_node->dir.x = atof(cursor + 5);
		cyl_node->dir.y = atof(tmp[i + 1]);
		cyl_node->dir.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("dir x = %f | y = %f | z = %f\n", cyl_node->dir.x, cyl_node->dir.y, cyl_node->dir.z);
	if ((cursor = ft_strstr(tmp[i], "radius=\"")) == NULL)
		s_error("\x1b[2;31mError in cylinder, RADIUS expected in #3\x1b[0m", e);
	else
	{
		cyl_node->radius = atof(cursor + 5);		
		i++;
	}
	printf("radius = %f\n", cyl_node->radius);
	if ((cursor = ft_strstr(tmp[i], "color=\"")) == NULL)
		s_error("\x1b[2;31mError in cylinder, COLOR expected in #4\x1b[0m", e);
	else
		cyl_node->color = ft_atoi(cursor + 7);
	printf("color = %d\n", cyl_node->color);
	if (XML->node_lst == NULL)
		XML->node_lst = cyl_node;
	else
		xml_list_add_first(&XML->node_lst, cyl_node);
	xml_node_clean(tmp);
	NCYL++;
}
