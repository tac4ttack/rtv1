/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:50:15 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/20 15:39:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fpoint		fdf_matrix_top_rot(t_fpoint pt, int angle)
{
	double	teta;
	double	cos_teta;
	double	sin_teta;

	teta = (double)angle * (M_PI / 180);
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	pt.x = pt.x * cos_teta - pt.y * sin_teta;
	pt.y = pt.x * sin_teta + pt.y * cos_teta;
	return (pt);
}

t_fpoint		fdf_matrix_rot_x(t_fpoint pt, int angle)
{
	double cos_teta;
	double sin_teta;
	double sin_teta_inv;
	double teta;

	teta = (double)angle * (M_PI / 180);
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	sin_teta_inv = -sin_teta;
	pt.y = (cos_teta * pt.y) + (sin_teta_inv * pt.z);
	pt.z = (sin_teta * pt.y) + (cos_teta * pt.z);
	return (pt);
}

t_fpoint		fdf_matrix_rot_y(t_fpoint pt, int angle)
{
	double cos_teta;
	double sin_teta;
	double sin_teta_inv;
	double teta;

	teta = (double)angle * (M_PI / 180);
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	sin_teta_inv = -sin_teta;
	pt.x = (cos_teta * pt.x) + (sin_teta * pt.z);
	pt.z = (sin_teta_inv * pt.x) + (cos_teta * pt.z);
	return (pt);
}

t_fpoint		fdf_matrix_rot_z(t_fpoint pt, int angle)
{
	double	cos_teta;
	double	sin_teta;
	double	sin_teta_inv;
	double	teta;
	int		vx;

	vx = pt.x;
	teta = (double)angle * (M_PI / 180);
	cos_teta = cos(teta);
	sin_teta = sin(teta);
	sin_teta_inv = -sin_teta;
	pt.x = (cos_teta * pt.x) + (sin_teta_inv * pt.y);
	pt.y = (sin_teta * vx) + (cos_teta * pt.y);
	return (pt);
}

t_fpoint		fdf_matrix_proj(t_env *env, t_fpoint pt)
{
	pt = fdf_matrix_rot_z(pt, env->r_z);
	if (env->p_mode != 4)
	{
		pt = fdf_matrix_rot_x(pt, env->r_x);
		pt = fdf_matrix_rot_y(pt, env->r_y);
	}
	return (pt);
}
