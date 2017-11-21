/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:07:10 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/21 11:07:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
