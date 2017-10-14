/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guides.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 18:26:51 by fmessina          #+#    #+#             */
/*   Updated: 2017/05/30 13:22:46 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			mid_guides(t_env *e)
{
	t_ldpt		pta;
	t_ldpt		ptb;
	t_ldpt		ptc;
	t_ldpt		ptd;

	pta.r = e->s_w / 2;
	pta.i = 0;
	ptb.r = e->s_w / 2;
	ptb.i = e->s_h;
	ptc.r = 0;
	ptc.i = e->s_h / 2;
	ptd.r = e->s_w;
	ptd.i = e->s_h / 2;
	mlx_img_line(e->sce, pta, ptb, 0x0000FF00);
	mlx_img_line(e->sce, ptc, ptd, 0x0000FF00);
}
