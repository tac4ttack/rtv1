/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_zoom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 13:18:50 by fmessina          #+#    #+#             */
/*   Updated: 2017/09/22 03:24:01 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mouse_zoom_in(t_env *e, int m_x, int m_y)
{
	e->off_x = m_x - (m_x - e->off_x) * 1.1;
	e->off_y = m_y - (m_y - e->off_y) * 1.1;
	e->sca *= 1.1;
}

void	mouse_zoom_out(t_env *e, int m_x, int m_y)
{
	e->off_x = m_x - (m_x - e->off_x) / 1.1;
	e->off_y = m_y - (m_y - e->off_y) / 1.1;
	e->sca /= 1.1;
}
