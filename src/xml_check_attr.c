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

int			xml_check_attnode(char *att, int j)
{
	int		ok;

	ok = 0;
	while(att[j])
	{
		if ((att[j] < 48 || att[j] > 57) && att[j] != '.' && att[j] != '-')
		{
			if (att[j] != ',' && att[j] != '"')
				return (1);
			ok = 1;
		//	printf("%s, erreur de pisse %c\n", att, att[j]);
			if (att[j + 1] != '\0' && att[j + 1] != '>')
				return (1);
		}
		if (att[j + 1] == '>')
			++j;
		++j;
	}
	if (ok == 0)
		return (1);
	return (0);
}

int			xml_check_attr(char **att)
{
	int		i;
	int		j;

	i = 1;
	while (att[i])
	{
		j = 0;
		if (att[i][j] >= 97 && att[i][j] <= 122)
			while(att[i][j] && att[i][j] != '=')
				j++;
		if (att[i][j] == 0)
			return (1);
		if(att[i][j] == '=')
			j += 2;
		//printf("indice : %i, %s, att : %s\n", j, att[0], att[i] + j);
		if (xml_check_attnode(att[i], j) == 1)
		{
			printf("error dans ce %s\n", att[i]);
			return (1);
		}
		++i;
		while (att[i] && (ft_strcmp(att[i], "/>") == 0 || \
		ft_strcmp(att[i], "-->") == 0 || ft_strcmp(att[i], "/>-->") == 0))
		++i;
	}
	return (0);
}