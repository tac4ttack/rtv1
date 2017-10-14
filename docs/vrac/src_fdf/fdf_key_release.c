/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_release.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:37:07 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/17 19:34:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	fdf_key_release_1(int key, t_env *env)
{
	(key == K_ESC ? env->keys.k_esc = 0 : 0);
	(key == K_LA ? env->keys.k_la = 0 : 0);
	(key == K_RA ? env->keys.k_ra = 0 : 0);
	(key == K_UA ? env->keys.k_ua = 0 : 0);
	(key == K_DA ? env->keys.k_da = 0 : 0);
	(key == K_A ? env->keys.k_a = 0 : 0);
	(key == K_B ? env->keys.k_b = 0 : 0);
	(key == K_C ? env->keys.k_c = 0 : 0);
	(key == K_D ? env->keys.k_d = 0 : 0);
	(key == K_E ? env->keys.k_e = 0 : 0);
	(key == K_F ? env->keys.k_f = 0 : 0);
	(key == K_G ? env->keys.k_g = 0 : 0);
	(key == K_H ? env->keys.k_h = 0 : 0);
	(key == K_I ? env->keys.k_i = 0 : 0);
	(key == K_J ? env->keys.k_j = 0 : 0);
	(key == K_K ? env->keys.k_k = 0 : 0);
	(key == K_L ? env->keys.k_l = 0 : 0);
	(key == K_M ? env->keys.k_m = 0 : 0);
	(key == K_N ? env->keys.k_n = 0 : 0);
	(key == K_O ? env->keys.k_o = 0 : 0);
	(key == K_P ? env->keys.k_p = 0 : 0);
	(key == K_Q ? env->keys.k_q = 0 : 0);
	(key == K_R ? env->keys.k_r = 0 : 0);
	(key == K_S ? env->keys.k_s = 0 : 0);
	(key == K_T ? env->keys.k_t = 0 : 0);
}

static	void	fdf_key_release_2(int key, t_env *env)
{
	(key == K_U ? env->keys.k_u = 0 : 0);
	(key == K_V ? env->keys.k_v = 0 : 0);
	(key == K_W ? env->keys.k_w = 0 : 0);
	(key == K_X ? env->keys.k_x = 0 : 0);
	(key == K_Y ? env->keys.k_y = 0 : 0);
	(key == K_Z ? env->keys.k_z = 0 : 0);
	(key == K_0 ? env->keys.k_0 = 0 : 0);
	(key == K_1 ? env->keys.k_1 = 0 : 0);
	(key == K_2 ? env->keys.k_2 = 0 : 0);
	(key == K_3 ? env->keys.k_3 = 0 : 0);
	(key == K_4 ? env->keys.k_4 = 0 : 0);
	(key == K_5 ? env->keys.k_5 = 0 : 0);
	(key == K_6 ? env->keys.k_6 = 0 : 0);
	(key == K_7 ? env->keys.k_7 = 0 : 0);
	(key == K_8 ? env->keys.k_8 = 0 : 0);
	(key == K_9 ? env->keys.k_9 = 0 : 0);
	(key == K_N0 ? env->keys.k_n0 = 0 : 0);
	(key == K_N1 ? env->keys.k_n1 = 0 : 0);
	(key == K_N2 ? env->keys.k_n2 = 0 : 0);
	(key == K_N3 ? env->keys.k_n3 = 0 : 0);
	(key == K_N4 ? env->keys.k_n4 = 0 : 0);
	(key == K_N5 ? env->keys.k_n5 = 0 : 0);
	(key == K_N6 ? env->keys.k_n6 = 0 : 0);
	(key == K_N7 ? env->keys.k_n7 = 0 : 0);
	(key == K_N8 ? env->keys.k_n8 = 0 : 0);
}

static	void	fdf_key_release_3(int key, t_env *env)
{
	(key == K_N9 ? env->keys.k_n9 = 0 : 0);
	(key == K_NSLA ? env->keys.k_nsla = 0 : 0);
	(key == K_NSTR ? env->keys.k_nstr = 0 : 0);
	(key == K_NMIN ? env->keys.k_nmin = 0 : 0);
	(key == K_NPLU ? env->keys.k_nplu = 0 : 0);
	(key == K_NENT ? env->keys.k_nent = 0 : 0);
	(key == K_NDOT ? env->keys.k_ndot = 0 : 0);
	(key == K_NEQU ? env->keys.k_nequ = 0 : 0);
	(key == K_NDEL ? env->keys.k_ndel = 0 : 0);
	(key == K_HOME ? env->keys.k_home = 0 : 0);
	(key == K_END ? env->keys.k_end = 0 : 0);
	(key == K_PGU ? env->keys.k_pgu = 0 : 0);
	(key == K_PGD ? env->keys.k_pgd = 0 : 0);
	(key == K_DEL ? env->keys.k_del = 0 : 0);
	(key == K_BSP ? env->keys.k_bsp = 0 : 0);
	(key == K_SPC ? env->keys.k_spc = 0 : 0);
	(key == K_LSHI ? env->keys.k_lshi = 0 : 0);
	(key == K_RSHI ? env->keys.k_rshi = 0 : 0);
	(key == K_LCTRL ? env->keys.k_lctrl = 0 : 0);
	(key == K_RCTRL ? env->keys.k_rctrl = 0 : 0);
	(key == K_LOPT ? env->keys.k_lopt = 0 : 0);
	(key == K_ROPT ? env->keys.k_ropt = 0 : 0);
	(key == K_LCMD ? env->keys.k_lcmd = 0 : 0);
	(key == K_RCMD ? env->keys.k_rcmd = 0 : 0);
	(key == K_COM ? env->keys.k_com = 0 : 0);
}

static	void	fdf_key_release_4(int key, t_env *env)
{
	(key == K_DOT ? env->keys.k_dot = 0 : 0);
	(key == K_SLA ? env->keys.k_sla = 0 : 0);
	(key == K_SCOL ? env->keys.k_scol = 0 : 0);
	(key == K_QUO ? env->keys.k_quo = 0 : 0);
	(key == K_LBRA ? env->keys.k_lbra = 0 : 0);
	(key == K_RBRA ? env->keys.k_rbra = 0 : 0);
	(key == K_BSLA ? env->keys.k_bsla = 0 : 0);
	(key == K_DASH ? env->keys.k_dash = 0 : 0);
	(key == K_EQU ? env->keys.k_equ = 0 : 0);
	(key == K_APO ? env->keys.k_apo = 0 : 0);
	(key == K_TAB ? env->keys.k_tab = 0 : 0);
	(key == K_CAPS ? env->keys.k_caps = 0 : 0);
	(key == K_RET ? env->keys.k_ret = 0 : 0);
	(key == K_FN ? env->keys.k_fn = 0 : 0);
	(key == K_F1 ? env->keys.k_f1 = 0 : 0);
	(key == K_F2 ? env->keys.k_f2 = 0 : 0);
	(key == K_F3 ? env->keys.k_f3 = 0 : 0);
	(key == K_F4 ? env->keys.k_f4 = 0 : 0);
	(key == K_F5 ? env->keys.k_f5 = 0 : 0);
	(key == K_F6 ? env->keys.k_f6 = 0 : 0);
	(key == K_F7 ? env->keys.k_f7 = 0 : 0);
	(key == K_F8 ? env->keys.k_f8 = 0 : 0);
	(key == K_F9 ? env->keys.k_f9 = 0 : 0);
	(key == K_F10 ? env->keys.k_f10 = 0 : 0);
	(key == K_F11 ? env->keys.k_f11 = 0 : 0);
}

int				fdf_key_release(int key, t_env *env)
{
	(key == K_F12 ? env->keys.k_f12 = 0 : 0);
	(key == K_F13 ? env->keys.k_f13 = 0 : 0);
	(key == K_F14 ? env->keys.k_f14 = 0 : 0);
	(key == K_F15 ? env->keys.k_f15 = 0 : 0);
	(key == K_F16 ? env->keys.k_f16 = 0 : 0);
	(key == K_F17 ? env->keys.k_f17 = 0 : 0);
	(key == K_F18 ? env->keys.k_f18 = 0 : 0);
	(key == K_F19 ? env->keys.k_f19 = 0 : 0);
	fdf_key_release_1(key, env);
	fdf_key_release_2(key, env);
	fdf_key_release_3(key, env);
	fdf_key_release_4(key, env);
	return (0);
}
