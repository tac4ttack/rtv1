/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   celtic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:29:08 by fmessina          #+#    #+#             */
/*   Updated: 2017/09/14 19:51:07 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			celtic_test(t_env *e, int x, int y)
{
	t_ldpt			c;
	t_ldpt			z;
	long double		tmp;
	int				i;

	i = 0;
	c.r = ((long double)x - e->off_x) / e->sca;
	c.i = ((long double)y - e->off_y) / e->sca;
	z.r = 0;
	z.i = 0;
	while (i < e->ite && e->mod < 4)
	{
		tmp = z.r;
		z.r = fabsl((tmp * tmp) - (z.i * z.i)) + c.r;
		z.i = 2 * z.i * tmp + c.i;
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

void				celtic(t_env *e)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (j < e->s_h)
	{
		while (i < e->s_w)
		{
			e->mod = 0;
			e->t = 0;
			celtic_test(e, i, j);
			i++;
		}
		i = 0;
		j++;
	}
}
