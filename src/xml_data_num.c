/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:32:12 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/22 19:04:31 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		xml_data_type(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading LIGHT TYPE value\x1b[0m", e);
		node->light = ft_atoi(attributes[(*i)++] + 6);
	}	
	else
		s_error("\x1b[2;31mError reading LIGHT TYPE from scene\x1b[0m", e);
}

void		xml_data_intens(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading INTENSITY value\x1b[0m", e);
		node->intensity = ft_atof(attributes[(*i)++] + 11);
	}
	else
		s_error("\x1b[2;31mError reading INTENSITY from scene\x1b[0m", e);
}

void		xml_data_radius(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading RADIUS value\x1b[0m", e);
		node->radius = ft_atof(attributes[(*i)++] + 8);
	}
	else
		s_error("\x1b[2;31mError reading RADIUS from scene\x1b[0m", e);
}

void		xml_data_angle(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading ANGLE value\x1b[0m", e);	
		node->angle = ft_atof(attributes[(*i)++] + 7);
	}
	else
		s_error("\x1b[2;31mError reading ANGLE from scene\x1b[0m", e);	
}

void		xml_data_color(t_env *e, char **attributes, int *i, t_node *node)
{
	int		channel[4];
	int		j;
	
	j = 0;
	ft_memset(channel, 0, 4 * sizeof(int));
	if (e && attributes && node)
	{
		while (j < 4)
		{
			if (attributes[(*i)] == NULL)
				s_error("\x1b[2;31mError reading COLOR value\x1b[0m", e);			
			if (j== 0)
				channel[j] = ft_atoi(attributes[(*i)++] + 7);
			else
				channel[j] = ft_atoi(attributes[(*i)++]);	
			j++;
		}
		node->color = ((channel[0] << 24) + (channel[1] << 16) + \
						(channel[2] << 8) + channel[3]);
	}
	else
		s_error("\x1b[2;31mError reading COLOR from scene\x1b[0m", e);	
}
