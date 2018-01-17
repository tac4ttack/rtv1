/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_ui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 15:03:16 by fmessina          #+#    #+#             */
/*   Updated: 2018/01/17 16:07:40 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

cl_float3		*get_target_dir(t_env *e)
{
	cl_float3	*res;
	
	res = NULL;
	if (ACTIVEOBJ.type != 0)
	{
		if (ACTIVEOBJ.type == 1)
		{
			printf("obj = %p | ", &CONES[ACTIVEOBJ.id].dir);
			res = &CONES[ACTIVEOBJ.id].dir;
		}
		else if (ACTIVEOBJ.type == 2)
		{			
			printf("obj = %p | ", &CYLIND[ACTIVEOBJ.id].dir);
			res = &CYLIND[ACTIVEOBJ.id].dir;
		}
		else if (ACTIVEOBJ.type == 4)
		{
			printf("obj = %p | ", &PLANE[ACTIVEOBJ.id].normale);
			res = &PLANE[ACTIVEOBJ.id].normale;
		}
		else
		{
			printf("obj = %p | ", &SPHERE[ACTIVEOBJ.id].dir);
			res = &SPHERE[ACTIVEOBJ.id].dir;
		}
	}
	printf("res = %p\n", res);
	return (res);
}

void			obj_rot(t_env *e, short unsigned int mode, float angle)
{
	cl_float3	*target_dir;
	
	target_dir = NULL;
	printf("target_dir1 = %p | ", target_dir);
	target_dir = get_target_dir(e);
	printf("target_dir2 = %p\n", target_dir);
	if (mode == 0)
		rotx(*target_dir, angle);
	else if (mode == 1)
		roty(*target_dir, angle);
	else
		rotz(*target_dir, angle);
}
