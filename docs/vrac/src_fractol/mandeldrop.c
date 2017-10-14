/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandeldrop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:59:03 by fmessina          #+#    #+#             */
/*   Updated: 2017/09/24 07:47:07 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void					mandeldroppow_test(t_env *e, int x, int y)
{
	long double _Complex	c;
	long double _Complex	z;
	int						i;

	i = 0;
	c = ((-(y - e->off_y) / e->sca) + ((x - e->off_x) / e->sca) * I);
	c = 1 / c;
	z = c;
	while (i < e->ite && e->mod < 4)
	{
		z = cpowf(z, e->p) + c;
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

static t_ldpt				init_the_drop(t_env *e, int x, int y)
{
	t_ldpt					result;
	long double				module;

	result.i = ((long double)x - e->off_x) / e->sca;
	result.r = (-((long double)y - e->off_y)) / e->sca;
	module = ((result.r * result.r) + (result.i * result.i));
	result.r = (result.r) / module;
	result.i = (-result.i) / module;
	return (result);
}

static void					mandeldrop_test(t_env *e, int x, int y)
{
	t_ldpt					c;
	t_ldpt					z;
	long double				tmp;
	int						i;

	i = 0;
	c = init_the_drop(e, x, y);
	z.r = c.r;
	z.i = c.i;
	while (i < e->ite && e->mod < 4)
	{
		tmp = z.r;
		z.r = (tmp * tmp) - (z.i * z.i) + c.r;
		z.i = (2 * z.i * tmp) + c.i;
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

void						mandeldrop(t_env *e)
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
				mandeldrop_test(e, i, j);
			else
				mandeldroppow_test(e, i, j);
			i++;
		}
		i = 0;
		j++;
	}
}
