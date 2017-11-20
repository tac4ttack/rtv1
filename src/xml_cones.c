/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cones.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:38 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/20 17:37:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	xml_node_cone(t_env *e, char *node)
{
	t_node	*cone_node;
	char	**tmp;
	char	*cursor;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	cone_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	if ((cursor = ft_strstr(tmp[i], "id=\"")) == NULL)
		s_error("\x1b[2;31mError in cone, ID expected in #0\x1b[0m", e);
	else
	{
		cone_node->id = ft_atoi(cursor + 4);
		i++;
	}
	printf("CONE id = %d\n", cone_node->id);
	if ((cursor = ft_strstr(tmp[i], "pos=\"")) == NULL)
		s_error("\x1b[2;31mError in cone, POS expected in #1\x1b[0m", e);
	else
	{
		cone_node->pos.x = atof(cursor + 5);
		cone_node->pos.y = atof(tmp[i + 1]);
		cone_node->pos.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("pos x = %f | y = %f | z = %f\n", cone_node->pos.x, cone_node->pos.y, cone_node->pos.z);
	if ((cursor = ft_strstr(tmp[i], "dir=\"")) == NULL)
		s_error("\x1b[2;31mError in cone, DIR expected in #2\x1b[0m", e);
	else
	{
		cone_node->dir.x = atof(cursor + 5);
		cone_node->dir.y = atof(tmp[i + 1]);
		cone_node->dir.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("dir x = %f | y = %f | z = %f\n", cone_node->dir.x, cone_node->dir.y, cone_node->dir.z);
	if ((cursor = ft_strstr(tmp[i], "angle=\"")) == NULL)
		s_error("\x1b[2;31mError in cone, ANGLE expected in #3\x1b[0m", e);
	else
	{
		cone_node->angle = atof(cursor + 7);
		i++;
	}
	printf("angle = %f\n", cone_node->angle);
	if ((cursor = ft_strstr(tmp[i], "color=\"")) == NULL)
		s_error("\x1b[2;31mError in cone, COLOR expected in #4\x1b[0m", e);
	else
		cone_node->color = ft_atoi(cursor + 7); // manque conversion hexa
	printf("color = %d\n", cone_node->color);
	if (XML->node_lst == NULL)
		XML->node_lst = cone_node;
	else
		xml_list_add_first(&XML->node_lst, cone_node);
	xml_node_clean(tmp);
	NCON++;
}
