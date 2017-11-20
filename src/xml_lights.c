/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:58 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/20 17:37:23 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	xml_node_light(t_env *e, char *node)
{
	t_node	*light_node;
	char	**tmp;
	char	*cursor;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	light_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	if ((cursor = ft_strstr(tmp[i], "id=\"")) == NULL)
		s_error("\x1b[2;31mError in light, ID expected in #0\x1b[0m", e);
	else
	{
		light_node->id = ft_atoi(cursor + 4);
		i++;
	}
	printf("LIGHT id = %d\n", light_node->id);
	if ((cursor = ft_strstr(tmp[i], "type=\"")) == NULL)
		s_error("\x1b[2;31mError in light, TYPE expected in #1\x1b[0m", e);
	else
	{
		light_node->type = ft_atoi(cursor + 6);
		i++;
	}
	printf("type = %d\n", light_node->type);
	if ((cursor = ft_strstr(tmp[i], "pos=\"")) == NULL)
		s_error("\x1b[2;31mError in light, POS expected in #2\x1b[0m", e);
	else
	{
		light_node->pos.x = atof(cursor + 5);
		light_node->pos.y = atof(tmp[i + 1]);
		light_node->pos.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("pos x = %f | y = %f | z = %f\n", light_node->pos.x, light_node->pos.y, light_node->pos.z);
	if ((cursor = ft_strstr(tmp[i], "dir=\"")) == NULL)
		s_error("\x1b[2;31mError in light, DIR expected in #3\x1b[0m", e);
	else
	{
		light_node->dir.x = atof(cursor + 5);
		light_node->dir.y = atof(tmp[i + 1]);
		light_node->dir.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("dir x = %f | y = %f | z = %f\n", light_node->dir.x, light_node->dir.y, light_node->dir.z);
	if ((cursor = ft_strstr(tmp[i], "intensity=\"")) == NULL)
		s_error("\x1b[2;31mError in light, INTENSITY expected in #4\x1b[0m", e);
	else
	{
		light_node->intensity = atof(cursor + 11);		
		i++;
	}
	printf("intensity = %f\n", light_node->intensity);
	if ((cursor = ft_strstr(tmp[i], "color=\"")) == NULL)
		s_error("\x1b[2;31mError in light, COLOR expected in #5\x1b[0m", e);
	else
		light_node->color = ft_atoi(cursor + 7);
	printf("color = %d\n", light_node->color);
	if (XML->node_lst == NULL)
		XML->node_lst = light_node;
	else
		xml_list_add_first(&XML->node_lst, light_node);
	xml_node_clean(tmp);
	NLIG++;
}
