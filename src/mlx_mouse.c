/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 09:39:21 by fmessina          #+#    #+#             */
/*   Updated: 2017/10/14 14:18:05 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		mlx_mouse_events(int btn, int x, int y, t_env *e)
{
//	instruction du dessous juste pour faire fermer sa gueule a clang
	btn = btn - 1 + 1;
	e->mou_x = x;
	e->mou_y = y;
	return (0);
}
