/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 19:03:38 by fmessina          #+#    #+#             */
/*   Updated: 2017/06/01 13:47:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Disabled keybinds
** (KP_N7 ? env->r_x++ : 0);
** (KP_N1 ? env->r_x-- : 0);
** (KP_N8 ? env->r_y++ : 0);
** (KP_N2 ? env->r_y-- : 0);
** (KP_N9 ? env->r_z++ : 0);
** (KP_N3 ? env->r_z-- : 0);
*/

#include "fdf.h"

static void		fdf_key_2(t_env *env)
{
	(KP_G == 1 ? env->r_mode = 0 : 0);
	(KP_P == 1 ? env->r_mode = 1 : 0);
	(KP_I == 1 ? env->p_mode = 2 : 0);
	(KP_NSTR == 1 ? fdf_options_init(env) : 0);
	(KP_T == 1 ? env->p_mode = 4 : 0);
	(KP_Z == 1 ? SC = 25 : 0);
	(KP_NPLU == 1 && SC < INT_MAX ? SC += 2 : 0);
	(KP_NMIN == 1 && SC > 1 ? SC -= 2 : 0);
	(KP_M == 1 && env->guides != 1 ? env->guides *= -1 : 0);
	(KP_COM == 1 && env->guides != -1 ? env->guides *= -1 : 0);
}

static void		fdf_key_1(t_env *env)
{
	(KP_RA == 1 ? env->off_x += 5 : 0);
	(KP_LA == 1 ? env->off_x -= 5 : 0);
	(KP_UA == 1 ? env->off_y -= 5 : 0);
	(KP_DA == 1 ? env->off_y += 5 : 0);
	(KP_ESC == 1 ? fdf_quit(env) : 0);
	(KP_NDEL == 1 ? fdf_reset_color(env) : 0);
	(KP_HOME == 1 && C_A > 0 ? HUE = fdf_color(C_A--, C_R, C_G, C_B) : 0);
	(KP_PGU == 1 && C_A < 255 ? HUE = fdf_color(C_A++, C_R, C_G, C_B) : 0);
	(KP_F13 == 1 && C_R < 255 ? HUE = fdf_color(C_A, C_R++, C_G, C_B) : 0);
	(KP_DEL == 1 && C_R > 0 ? HUE = fdf_color(C_A, C_R--, C_G, C_B) : 0);
	(KP_F14 == 1 && C_G < 255 ? HUE = fdf_color(C_A, C_R, C_G++, C_B) : 0);
	(KP_END == 1 && C_G > 0 ? HUE = fdf_color(C_A, C_R, C_G--, C_B) : 0);
	(KP_F15 == 1 && C_B < 255 ? HUE = fdf_color(C_A, C_R, C_G, C_B++) : 0);
	(KP_PGD == 1 && C_B > 0 ? HUE = fdf_color(C_A, C_R, C_G, C_B--) : 0);
	(KP_NEQU == 1 ? ZSC -= 0.01 : 0);
	(KP_NSLA == 1 ? ZSC += 0.01 : 0);
	if (KP_C == 1)
	{
		env->off_x = 0;
		env->off_y = 0;
	}
}

void			fdf_keyboard(t_env *env)
{
	if (env == NULL)
		exit(EXIT_FAILURE);
	fdf_key_1(env);
	fdf_key_2(env);
}
