/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_guides.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 00:03:43 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/20 15:40:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_mid_guides(t_env *env)
{
	t_fpoint		pta;
	t_fpoint		ptb;
	t_fpoint		ptc;
	t_fpoint		ptd;

	pta.x = env->s_w / 2;
	pta.y = 0;
	ptb.x = env->s_w / 2;
	ptb.y = env->s_h;
	ptc.x = 0;
	ptc.y = env->s_h / 2;
	ptd.x = env->s_w;
	ptd.y = env->s_h / 2;
	fdf_img_line(env, pta, ptb, 0x0000FF00);
	fdf_img_line(env, ptc, ptd, 0x0000FF00);
}

void			fdf_outline_img(t_env *env)
{
	t_fpoint		pa;
	t_fpoint		pb;
	t_fpoint		pc;
	t_fpoint		pd;

	pa.x = 1;
	pa.y = 1;
	pb.x = env->s_w - 1;
	pb.y = 1;
	pc.x = env->s_w - 1;
	pc.y = env->s_h - 1;
	pd.x = 1;
	pd.y = env->s_h - 1;
	fdf_img_line(env, pa, pb, 0x00FF0000);
	fdf_img_line(env, pb, pc, 0x00FF0000);
	fdf_img_line(env, pc, pd, 0x00FF0000);
	fdf_img_line(env, pd, pa, 0x00FF0000);
}
