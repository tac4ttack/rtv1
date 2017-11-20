/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:26 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/20 17:37:40 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	xml_node_sphere(t_env *e, char *node)
{
	t_node	*sphere_node;
	char	**tmp;
	char	*cursor;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	sphere_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	if ((cursor = ft_strstr(tmp[i], "id=\"")) == NULL)
		s_error("\x1b[2;31mError in sphere, ID expected in #0\x1b[0m", e);
	else
	{
		sphere_node->id = ft_atoi(cursor + 4);
		i++;
	}
	printf("SPHERE id = %d\n", sphere_node->id);
	if ((cursor = ft_strstr(tmp[i], "pos=\"")) == NULL)
		s_error("\x1b[2;31mError in sphere, POS expected in #1\x1b[0m", e);
	else
	{
		sphere_node->pos.x = atof(cursor + 5);
		sphere_node->pos.y = atof(tmp[i + 1]);
		sphere_node->pos.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("pos x = %f | y = %f | z = %f\n", sphere_node->pos.x, sphere_node->pos.y, sphere_node->pos.z);
	if ((cursor = ft_strstr(tmp[i], "dir=\"")) == NULL)
		s_error("\x1b[2;31mError in sphere, DIR expected in #2\x1b[0m", e);
	else
	{
		sphere_node->dir.x = atof(cursor + 5);
		sphere_node->dir.y = atof(tmp[i + 1]);
		sphere_node->dir.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("dir x = %f | y = %f | z = %f\n", sphere_node->dir.x, sphere_node->dir.y, sphere_node->dir.z);
	if ((cursor = ft_strstr(tmp[i], "radius=\"")) == NULL)
		s_error("\x1b[2;31mError in sphere, RADIUS expected in #3\x1b[0m", e);
	else
	{
		sphere_node->radius = atof(cursor + 5);		
		i++;
	}
	printf("radius = %f\n", sphere_node->radius);
	if ((cursor = ft_strstr(tmp[i], "color=\"")) == NULL)
		s_error("\x1b[2;31mError in sphere, COLOR expected in #4\x1b[0m", e);
	else
		sphere_node->color = ft_atoi(cursor + 7);
	printf("color = %d\n", sphere_node->color);
	if (XML->node_lst == NULL)
		XML->node_lst = sphere_node;
	else
		xml_list_add_first(&XML->node_lst, sphere_node);
	xml_node_clean(tmp);
	NSPH++;
}
