/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cameras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:04 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/20 17:36:50 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		xml_node_cam(t_env *e, char *node)
{
	t_node	*cam_node;
	char	**tmp;
	char	*cursor;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	cam_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	if ((cursor = ft_strstr(tmp[i], "id=\"")) == NULL)
		s_error("\x1b[2;31mError in camera, ID expected in #0\x1b[0m", e);
	else
	{
		cam_node->id = ft_atoi(cursor + 4);
		i++;
	}
	printf("CAMERA id = %d\n", cam_node->id);
	if ((cursor = ft_strstr(tmp[i], "pos=\"")) == NULL)
		s_error("\x1b[2;31mError in camera, POS expected in #1\x1b[0m", e);
	else
	{
		cam_node->pos.x = atof(cursor + 5);
		cam_node->pos.y = atof(tmp[i + 1]);
		cam_node->pos.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("pos x = %f | y = %f | z = %f\n", cam_node->pos.x, cam_node->pos.y, cam_node->pos.z);
	if ((cursor = ft_strstr(tmp[i], "dir=\"")) == NULL)
		s_error("\x1b[2;31mError in camera, DIR expected in #2\x1b[0m", e);
	else
	{
		cam_node->dir.x = atof(cursor + 5);
		cam_node->dir.y = atof(tmp[i + 1]);
		cam_node->dir.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("dir x = %f | y = %f | z = %f\n", cam_node->dir.x, cam_node->dir.y, cam_node->dir.z);
	if ((cursor = ft_strstr(tmp[i], "hor=\"")) == NULL)
		s_error("\x1b[2;31mError in camera, HOR expected in #3\x1b[0m", e);
	else
	{
		cam_node->hor.x = atof(cursor + 5);
		cam_node->hor.y = atof(tmp[i + 1]);
		cam_node->hor.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("hor x = %f | y = %f | z = %f\n", cam_node->hor.x, cam_node->hor.y, cam_node->hor.z);
	if ((cursor = ft_strstr(tmp[i], "ver=\"")) == NULL)
		s_error("\x1b[2;31mError in camera, VER expected in #4\x1b[0m", e);
	else
	{
		cam_node->ver.x = atof(cursor + 5);
		cam_node->ver.y = atof(tmp[i + 1]);
		cam_node->ver.z = atof(tmp[i + 2]);			
		i += 3;
	}
	printf("ver x = %f | y = %f | z = %f\n", cam_node->ver.x, cam_node->ver.y, cam_node->ver.z);
	if (XML->node_lst == NULL)
		XML->node_lst = cam_node;
	else
		xml_list_add_first(&XML->node_lst, cam_node);
	xml_node_clean(tmp);
	NCAM++;
}
