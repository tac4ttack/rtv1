/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 00:46:33 by fmessina          #+#    #+#             */
/*   Updated: 2017/10/03 17:58:21 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	s_error(char *str)
{
	ft_putendl("\nOh no I just crashed!");
	ft_putendl(str);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	ft_putendl("\nOh no I just crashed!");
	perror(NULL);
	exit(EXIT_FAILURE);
}

int		quit(t_env *e)
{
	mlx_destroy_image(e->mlx, e->scene->ptr);
	mlx_destroy_window(e->mlx, e->win);
	free(e);
	ft_putendl("Exiting");
	exit(EXIT_SUCCESS);
	return (0);
}
