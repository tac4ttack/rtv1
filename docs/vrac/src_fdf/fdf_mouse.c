/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 19:12:38 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/17 20:56:36 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_mouse_events(int btn, int x, int y, t_env *env)
{
	env->mouse_x = x;
	env->mouse_y = y;
	(btn == 4 ? SC += 2 : btn);
	(SC > 1 && btn == 5 ? SC -= 2 : btn);
	fdf_refresh(env);
	return (0);
}
