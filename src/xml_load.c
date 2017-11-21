/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 03:44:24 by adalenco          #+#    #+#             */
/*   Updated: 2017/11/21 08:18:38 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		ft_atof(char *str)
{
	float	n;
	int		i;
	float	div;

	div = 10.0;
	i = 0;
	n = (float)ft_atoi(str);
	while (str[i] <= '9' && str[i] >= '0')
		++i;
	if (str[i] != '.')
		return (n);
	++i;
	while (str[i] <= '9' && str[i] >= '0')
	{ 
		n += ((str[i] - '0') / div);
		div *= 10.0;
		++i;
	}
	return (n);
}

int			load_file(t_env *e)
{
	int		i = 6;
	if (ft_strstr(SCN, "<scene>") != SCN)
		return (1);
	printf("%f\n", ft_atof("0.6"));
	while (SCN[i])
	{
		if (ft_strstr(SCN + i, "<cam"))
		{
			;
		}
		if (ft_strstr(SCN + i, "<light"))
			;
		if (ft_strstr(SCN + i, "<sphere"))
			;
		if (ft_strstr(SCN + i, "<plane"))
			;
		if (ft_strstr(SCN + i, "<cylinder"))
			;
		if (ft_strstr(SCN + i, "<cone"))
			;
		++i;
	}
	return (0);
}
