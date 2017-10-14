/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 19:59:16 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/21 01:13:50 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		fdf_scene_init(t_env *env)
{
	int			bpp;
	int			s_l;
	int			endian;

	env->p_scene = mlx_new_image(env->mlx, env->s_w, env->s_h);
	env->scene = mlx_get_data_addr(env->p_scene, &(bpp), &(s_l), &(endian));
	env->bpp = bpp;
	env->s_l = s_l;
	env->endian = endian;
	MID.x = (((float)FP.x + (float)LP.x) / 2);
	MID.y = (((float)FP.y + (float)LP.y) / 2);
	MID.z = 0;
	return (0);
}

static void		fdf_screen_setup(t_env *env)
{
	char		*buf;
	char		*cmd;
	char		**dim;
	int			fd;

	cmd = ft_strjoin(CMD1, CMD2);
	system(cmd);
	free(cmd);
	get_next_line(fd = open("./config", O_RDONLY), &buf);
	dim = NULL;
	dim = ft_strsplit(buf, 'x');
	env->m_w = ft_atoi(dim[0]);
	env->m_h = ft_atoi(dim[1]) - 100;
	env->w_w = (env->map.r * 100 > env->m_w ? env->m_w : env->map.r * 60);
	env->w_h = (env->map.l * 100 > env->m_h ? env->m_h : env->map.l * 60);
	(env->w_w < 800 ? env->w_w = 800 : 0);
	(env->w_h < 600 ? env->w_h = 600 : 0);
	env->s_w = env->w_w - 80;
	env->s_h = env->w_h - 80;
	env->s_x = 40;
	env->s_y = 40;
	close(fd);
	fdf_flush(dim);
	free(buf);
}

void			fdf_options_init(t_env *env)
{
	C_A = 0;
	C_R = 255;
	C_G = 255;
	C_B = 255;
	HUE = fdf_color(C_A, C_R, C_G, C_B);
	SC = 25;
	ZSC = 0.25;
	env->r_mode = 0;
	env->p_mode = 2;
	env->off_x = 0;
	env->off_y = 0;
	env->off_z = 0;
	env->r_x = 0;
	env->r_y = 0;
	env->r_z = 0;
	env->guides = -1;
	env->topo = 0;
}

void			fdf_init(t_env *env)
{
	fdf_screen_setup(env);
	fdf_options_init(env);
	if (!(env->mlx = mlx_init()))
		fdf_error("Error -> can't initialize minilibx server connexion");
	if (!(env->win = mlx_new_window(env->mlx, env->w_w, env->w_h, MW_NAME)))
		fdf_error("Error -> minilibx window creation failed");
	env->pos = 0;
	fdf_scene_init(env);
}
