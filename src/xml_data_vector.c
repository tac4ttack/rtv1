/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:05:41 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/21 12:27:24 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// pos = 0
// dir = 1
// hor = 2
// ver = 3
// nor = 4

void		xml_data_pos(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		node->pos.x = ft_atof(attributes[(*i)++] + 5);
		node->pos.y = ft_atof(attributes[(*i)++]);
		node->pos.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[2;31mError reading POS vector from scene\x1b[0m", e);	
}

void		xml_data_dir(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		node->dir.x = ft_atof(attributes[(*i)++] + 5);
		node->dir.y = ft_atof(attributes[(*i)++]);
		node->dir.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[2;31mError reading POS vector from scene\x1b[0m", e);	
}

void		xml_data_hor(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		node->hor.x = ft_atof(attributes[(*i)++] + 5);
		node->hor.y = ft_atof(attributes[(*i)++]);
		node->hor.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[2;31mError reading POS vector from scene\x1b[0m", e);	
}

void		xml_data_ver(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		node->ver.x = ft_atof(attributes[(*i)++] + 5);
		node->ver.y = ft_atof(attributes[(*i)++]);
		node->ver.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[2;31mError reading POS vector from scene\x1b[0m", e);	
}

void		xml_data_normale(t_env *e, char **attributes, int *i, t_node *node)
{
	if (node && attributes && e)
	{
		node->normale.x = ft_atof(attributes[(*i)++] + 9);
		node->normale.y = ft_atof(attributes[(*i)++]);
		node->normale.z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[2;31mError reading POS vector from scene\x1b[0m", e);	
}
