/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_cameras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:04 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/23 16:40:14 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	xml_cam_data(t_env *e, char **att, t_node *cam_node, int *i)
{
	if (ft_strncmp(att[*i], "id=\"", 4) != 0)
		s_error("\x1b[2;31mError in camera, ID expected in #0\x1b[0m", e);
	if (ft_atoi(att[(*i)] + 4) != NCAM - 1)
		s_error("\x1b[2;31mError in camera, ID is incorrect\x1b[0m", e);
	else
		cam_node->id = ft_atoi(att[(*i)++] + 4);
//	printf("CAMERA id = %d\n", cam_node->id);
	if (ft_strncmp(att[*i], "pos=\"", 5) != 0)
		s_error("\x1b[2;31mError in camera, POS expected in #1\x1b[0m", e);
	else
		xml_data_pos(e, att, i, cam_node);
//	printf("pos x = %f | y = %f | z = %f\n", cam_node->pos.x, cam_node->pos.y, cam_node->pos.z);
	if (ft_strncmp(att[*i], "dir=\"", 5) != 0)
		s_error("\x1b[2;31mError in camera, DIR expected in #2\x1b[0m", e);
	else
		xml_data_dir(e, att, i, cam_node);
//	printf("dir x = %f | y = %f | z = %f\n", cam_node->dir.x, cam_node->dir.y, cam_node->dir.z);
	if (ft_strncmp(att[*i], "hor=\"", 5) != 0)
	s_error("\x1b[2;31mError in camera, HOR expected in #3\x1b[0m", e);
	else
		xml_data_hor(e, att, i, cam_node);
//	printf("hor x = %f | y = %f | z = %f\n", cam_node->hor.x, cam_node->hor.y, cam_node->hor.z);
	if (ft_strncmp(att[*i], "ver=\"", 5) != 0)
		s_error("\x1b[2;31mError in camera, VER expected in #4\x1b[0m", e);
	else
		xml_data_ver(e, att, i, cam_node);
//	printf("ver x = %f | y = %f | z = %f\n", cam_node->ver.x, cam_node->ver.y, cam_node->ver.z);
}

void		xml_node_cam(t_env *e, char *node)
{
	t_node	*cam_node;
	char	**tmp;
	int		i;
	
	if (XML->in_scene != 1)
		s_error("\x1b[2;31mError node is outside scene\x1b[0m", e);
	NCAM++;
	cam_node = xml_list_new(0);
	tmp = ft_strsplit(node, ' ');
	i = 1;
	xml_cam_data(e, tmp, cam_node, &i);
	cam_node->type = 0;
	if (XML->node_lst == NULL)
		XML->node_lst = cam_node;
	else
		xml_list_add_first(&XML->node_lst, cam_node);
	xml_node_clean(tmp);
}

void		xml_allocate_cam(t_env *e)
{
	if (NCAM > 0)
	{
		if (!(e->cameras = malloc(sizeof(t_cam) * NCAM)))
			s_error("\x1b[2;31mCan't create cameras array\x1b[0m", e);
	}
	else
		e->cameras = NULL;
}

void		xml_push_cam(t_env *e, t_node *list)
{
	e->cameras[list->id].pos = list->pos;
	e->cameras[list->id].dir = list->dir;
	e->cameras[list->id].hor = list->hor;
	e->cameras[list->id].ver = list->ver;
}
