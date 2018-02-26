/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:47:00 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/26 19:47:00 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			mlx_keyboard_repeated(t_env *e)
{
	if (!e)
		exit(EXIT_FAILURE);
	(KP_ESC ? quit(e) : 0);
	if (KP_W || KP_S || KP_A || KP_D || KP_C || KP_SPC || \
		KP_DA || KP_UA || KP_LA || KP_RA || KP_Z)
		ui_cam(e);
	if (KP_I || KP_J || KP_K || KP_L || KP_U || KP_O || \
		KP_N4 || KP_N6 || KP_N8 || KP_N5 || KP_N7 || KP_N9)
		ui_obj(e);
	if (KP_NMIN || KP_NPLU)
	{
		if (KP_NPLU)
			e->scene->depth++;
		if (KP_NMIN)
			(e->scene->depth > 0 ? e->scene->depth-- : 0);
		if (tor_flush(e) != 0)
			s_error("\x1b[2;31mError flushing the Tree of Ray\x1b[0m", e);
		e->tree = tor_create(e);
	}
	if (KP_1)
	{
		if (e->scene->flag & OPTION_WAVE)
			e->scene->flag ^= OPTION_WAVE;
		else
			e->scene->flag |= OPTION_WAVE;
	}
	opencl_allocate_scene_memory(e);
}
