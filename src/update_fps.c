/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 18:22:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/02/22 22:48:57 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		update_fps(t_fps *fps)
{
	gettimeofday(&fps->step2, NULL);
	if (fps->fps)
	{
		fps->delta_time = (float)(fps->step2.tv_usec - fps->cur.tv_usec)
													/ 1000000;
		if (fps->delta_time < 0.005)
			fps->delta_time = 0.005;
		if (fps->cur.tv_sec != fps->step2.tv_sec)
			fps->delta_time = (float)(fps->step2.tv_usec +
								(1000000 - fps->cur.tv_usec)) / 1000000;
	}
	gettimeofday(&fps->cur, NULL);
	if (fps->cur.tv_sec - fps->step.tv_sec)
	{
		fps->ret_fps = fps->fps;
	//	ft_putstr("FPS ["); //FPS counter moved on hud
	//	ft_putnbr(fps->ret_fps);
	//	ft_putstr("]\n");
		fps->fps = 0;
		gettimeofday(&fps->step, NULL);
	}
	fps->fps++;
}
