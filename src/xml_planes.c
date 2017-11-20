/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_planes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:46 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/20 17:37:47 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	xml_node_plane(t_env *e, char *node)
{
	t_node	*plane_node;
	char	**tmp;
	char	*cursor;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	plane_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	if ((cursor = ft_strstr(tmp[i], "id=\"")) == NULL)
		s_error("\x1b[2;31mError in plane, ID expected in #0\x1b[0m", e);
	else
	{
		plane_node->id = ft_atoi(cursor + 4);
		i++;
	}
	printf("PLANE id = %d\n", plane_node->id);
	if ((cursor = ft_strstr(tmp[i], "pos=\"")) == NULL)
		s_error("\x1b[2;31mError in plane, POS expected in #1\x1b[0m", e);
	else
	{
		plane_node->pos.x = atof(cursor + 5);
		plane_node->pos.y = atof(tmp[i + 1]);
		plane_node->pos.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("pos x = %f | y = %f | z = %f\n", plane_node->pos.x, plane_node->pos.y, plane_node->pos.z);
	if ((cursor = ft_strstr(tmp[i], "normale=\"")) == NULL)
		s_error("\x1b[2;31mError in plane, NORMALE expected in #2\x1b[0m", e);
	else
	{
		plane_node->normale.x = atof(cursor + 5);
		plane_node->normale.y = atof(tmp[i + 1]);
		plane_node->normale.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("dir x = %f | y = %f | z = %f\n", plane_node->dir.x, plane_node->dir.y, plane_node->dir.z);
	if ((cursor = ft_strstr(tmp[i], "color=\"")) == NULL)
		s_error("\x1b[2;31mError in plane, COLOR expected in #3\x1b[0m", e);
	else
		plane_node->color = ft_atoi(cursor + 7);
	printf("color = %d\n", plane_node->color);
	if (XML->node_lst == NULL)
		XML->node_lst = plane_node;
	else
		xml_list_add_first(&XML->node_lst, plane_node);
	xml_node_clean(tmp);
	NPLA++;
}

