/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:16:55 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/20 19:28:28 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	fdf_check_map(t_env *env)
{
	PTS = ROWS * LINES;
	(ROWS < 2 ? fdf_error("Invalid map (2x2 minimun size required)") : 0);
	(LINES < 1 ? fdf_error("Invalid map (2x2 minimun size required)") : 0);
	(PTS < 3 ? fdf_error("Invalid map (2x2 minimun size required)") : 0);
}

int				main(int ac, char **av)
{
	t_env		env;

	if (ac == 2)
	{
		env.map.l = 0;
		env.map.r = -1;
		env.map.zmax = 0;
		env.map = fdf_file_read(av[1], &env.map);
		fdf_check_map(&env);
	}
	else
		fdf_error("Usage : ./fdf <filename>");
	fdf_init(&env);
	mlx_string_put(env.mlx, env.win, 10, 5, 0x0000FF00, av[1]);
	fdf_refresh(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.p_scene, env.s_x, env.s_y);
	mlx_hook(env.win, DestroyNotify, KeyReleaseMask, fdf_quit, &env);
	mlx_hook(env.win, KeyPress, KeyPressMask, fdf_key_press, &env);
	mlx_hook(env.win, KeyRelease, KeyReleaseMask, fdf_key_release, &env);
	mlx_mouse_hook(env.win, fdf_mouse_events, &env);
	mlx_loop_hook(env.mlx, fdf_loop_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
