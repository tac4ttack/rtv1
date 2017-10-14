/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mutate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:18:17 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/21 01:12:50 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fpoint		fdf_mutate_top(t_env *env, int i)
{
	t_fpoint		ret;

	ret.x = env->map.p_map[i].x * SC;
	ret.y = env->map.p_map[i].y * SC;
	ret.x -= (ROWS * SC / 2);
	ret.y -= (LINES * SC / 2);
	ret = fdf_matrix_proj(env, ret);
	ret.x += (ROWS * SC / 2);
	ret.y += (LINES * SC / 2);
	ret.x += (env->s_w / 2) + env->off_x - ((ROWS * SC) / 2) - (SC / 2);
	ret.y += (env->s_h / 2) + env->off_y - ((LINES * SC) / 2) - (SC / 2);
	return (ret);
}

static t_fpoint		fdf_mutate_game_iso(t_env *env, int i)
{
	int				x;
	int				y;
	t_fpoint		pt;
	t_fpoint		ret;

	pt.x = (float)env->map.p_map[i].x - MID.x;
	pt.y = (float)env->map.p_map[i].y - MID.y;
	pt.z = (float)env->map.p_map[i].z;
	ret.x = ((pt.x - pt.y) * SC);
	ret.y = ((pt.z * ((0 - ZSC) * SC)) + (pt.x + pt.y) * SC / 2);
	x = (env->s_w / 2) + env->off_x;
	y = (env->s_h / 2) + env->off_y;
	ret.x += x;
	ret.y += y;
	return (ret);
}

t_fpoint			fdf_mutate(t_env *env, int i)
{
	t_fpoint		ret;

	if (env->p_mode == 2)
		ret = fdf_mutate_game_iso(env, i);
	else if (env->p_mode == 4)
		ret = fdf_mutate_top(env, i);
	else
		ret = fdf_mutate_game_iso(env, i);
	return (ret);
}
