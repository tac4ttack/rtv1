/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 00:46:33 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/20 22:27:49 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

int				fdf_quit(t_env *env)
{
	mlx_destroy_image(env->mlx, env->p_scene);
	mlx_destroy_window(env->mlx, env->win);
	free(env->map.p_map);
	ft_putendl_fd("Exiting", 2);
	exit(EXIT_SUCCESS);
	return (0);
}
