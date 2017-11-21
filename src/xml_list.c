/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:46:52 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/20 15:07:40 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_node		*xml_list_new(char type)
{
	t_node	*new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	ft_bzero(new, sizeof(t_node));
	new->type = type;
	new->next = NULL;
	return (new);
}

void		xml_list_add_first(t_node **begin, t_node *node)
{
	if (node != NULL)
	{
		node->next = *begin;
		*begin = node;
	}
}

// USELESS? on a pas vraiment besoin de manipuler ces merdes
void		xml_list_add_last(t_node **begin, t_node *node)
{
	t_node	*tmp;

	tmp = *begin;
	if (node != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->next = NULL;
	}
}
