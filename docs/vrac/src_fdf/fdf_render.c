/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:29:22 by fmessina          #+#    #+#             */
/*   Updated: 2017/06/01 13:45:24 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_refresh(t_env *env)
{
	int			bpp;
	int			s_l;
	int			endian;

	mlx_clear_window(env->mlx, env->win);
	mlx_destroy_image(env->mlx, env->p_scene);
	env->p_scene = mlx_new_image(env->mlx, env->s_w, env->s_h);
	env->scene = mlx_get_data_addr(env->p_scene, &(bpp), &(s_l), &(endian));
	env->bpp = bpp;
	env->s_l = s_l;
	env->endian = endian;
	(env->r_mode == 0 ? fdf_render_grid(env) : NULL);
	(env->r_mode == 1 ? fdf_render_points(env) : NULL);
	(env->guides == 1 ? fdf_mid_guides(env) : NULL);
	fdf_outline_img(env);
	mlx_put_image_to_window(env->mlx, env->win, env->p_scene,
							env->s_x, env->s_y);
}

void			fdf_render_points(t_env *env)
{
	int			i;
	t_fpoint	pt;

	i = 0;
	while (i < (env->map.l * env->map.r))
	{
		pt = fdf_mutate(env, i);
		fdf_img_pix_put(env, pt.x, pt.y, HUE);
		i++;
	}
}

void			fdf_render_grid(t_env *env)
{
	int			i;
	int			j;
	t_fpoint	pta;
	t_fpoint	ptb;

	i = 0;
	j = 0;
	while ((i + (j * env->map.r)) < (env->map.l * env->map.r))
	{
		env->pos = i + (j * env->map.r);
		pta = fdf_mutate(env, env->pos);
		if (env->map.p_map[env->pos].x < env->map.r)
		{
			ptb = fdf_mutate(env, env->pos + 1);
			fdf_img_line(env, pta, ptb, HUE);
		}
		if (env->map.p_map[env->pos].y < env->map.l)
		{
			ptb = fdf_mutate(env, env->map.r + env->pos);
			fdf_img_line(env, pta, ptb, HUE);
		}
		i++;
		(i == (env->map.r) ? j++ : i);
		(i == (env->map.r) ? i = 0 : i);
	}
}
