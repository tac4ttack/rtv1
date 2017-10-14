/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricornpow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:52:46 by fmessina          #+#    #+#             */
/*   Updated: 2017/09/14 19:51:15 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void					tricornpow_test(t_env *e, int x, int y)
{
	long double _Complex	c;
	long double _Complex	z;
	int						i;

	i = 0;
	c = ((x - e->off_x) / e->sca) + (((y - e->off_y) / e->sca) * I);
	z = 0 + (0 * I);
	while (i < e->ite && e->mod < 4)
	{
		z = cpowf(conjf(z), e->p) + c;
		e->mod = crealf(z) * crealf(z) + cimagf(z) * cimagf(z);
		if (e->mode == 8)
			e->t += 0.5 * sinf(e->dof_s * z) + 0.5;
		i++;
	}
	if (i == e->ite)
		mlx_img_pix_put(e->sce, x, y, 0x00000000);
	else
		put_color(e, x, y, i);
}

static void					tricorn_test(t_env *e, int x, int y)
{
	t_ldpt					c;
	t_ldpt					z;
	long double				tmp;
	int						i;

	i = 0;
	c.r = ((long double)x - e->off_x) / e->sca;
	c.i = ((long double)y - e->off_y) / e->sca;
	z.r = 0;
	z.i = 0;
	while (i < e->ite && e->mod < 4)
	{
		tmp = z.r;
		z.r = (z.r * z.r) - (z.i * z.i) - c.r;
		z.i = (-2 * z.i * tmp) + c.i;
		e->mod = (z.r * z.r) + (z.i * z.i);
		if (e->mode == 8)
			e->t += 0.5 * sinf(e->dof_s * CMPLXF(z.r, z.i)) + 0.5;
		i++;
	}
	if (i == e->ite)
		mlx_img_pix_put(e->sce, x, y, 0x00000000);
	else
		put_color(e, x, y, i);
}

void						tricornpow(t_env *e)
{
	int						i;
	int						j;

	i = 0;
	j = 0;
	while (j < e->s_h)
	{
		while (i < e->s_w)
		{
			e->mod = 0;
			e->t = 0;
			if (e->p == 2)
				tricorn_test(e, i, j);
			else
				tricornpow_test(e, i, j);
			i++;
		}
		i = 0;
		j++;
	}
}
