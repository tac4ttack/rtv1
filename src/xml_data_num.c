/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:32:12 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/21 15:58:23 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		xml_data_type(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
		node->type = ft_atoi(attributes[(*i)++] + 6);
	else
		s_error("\x1b[2;31mError reading TYPE from scene\x1b[0m", e);
}

void		xml_data_intens(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
		node->intensity = ft_atof(attributes[(*i)++] + 11);
	else
		s_error("\x1b[2;31mError reading INTENSITY from scene\x1b[0m", e);
}

void		xml_data_radius(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
		node->radius = ft_atof(attributes[(*i)++] + 8);
	else
		s_error("\x1b[2;31mError reading RADIUS from scene\x1b[0m", e);
}

void		xml_data_angle(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
		node->angle = ft_atof(attributes[(*i)++] + 7);
	else
		s_error("\x1b[2;31mError reading ANGLE from scene\x1b[0m", e);	
}

// FAIRE UNE VRAI FONCTION QUI VA RECUP LA COULEUR HEXA
void		xml_data_color(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
		node->color = ft_atoi(attributes[(*i)++] + 7);
	else
		s_error("\x1b[2;31mError reading COLOR from scene\x1b[0m", e);	
}
