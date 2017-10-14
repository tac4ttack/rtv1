/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 19:08:55 by fmessina          #+#    #+#             */
/*   Updated: 2017/10/14 14:11:11 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(void)
{
	t_env *e;

	if (!(e = malloc(sizeof(t_env))))
		s_error("\x1b[2;31mCan't initialize RTv1 environment\x1b[0m");
	init(e);
	return (0);
}
