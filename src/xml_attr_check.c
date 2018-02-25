/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_attr_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 16:28:15 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/25 16:28:18 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
int			xml_attr_check(char *attr, int dec, int type)// type 1 ',', type 2 '"'
{
	while (attr[dec])
	{
		if (attr[dec] < 48 && attr[dec] > 57)
		{
			if (attr[dec + 1] != '\0')
				return (1);
			if ((type == 1 && attr[dec] != ',') || type == 2 && attr[dec] != '"')
				return (1);
		}
		++dec;
	}
	return (0);
}
*/
int			xml_attr_check(char **att)
{
	int		i;
	int		j

	i = 1;
	while (att[i])
	{
		j = 0;
		while(att[i][j] && att[i][j] != '=')
			j++;
		if (att[i][j] == 0)
			return (1);
		while(att[i][j])
		{
			if (att[i][j] < 48 && att[i][j] > 57 && att[i][j] != '.' && att[i][j] != '-')
				if (att[i][j + 1] != '\0' || (att[i][j] != ',' && att[i][j] != '"'))
					return (1);
			++j;
		}
		++i;
	}
	return (0);
}