/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_press.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:36:58 by fmessina          #+#    #+#             */
/*   Updated: 2017/04/17 19:34:32 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	fdf_key_press_1(int key, t_env *env)
{
	(key == K_ESC ? env->keys.k_esc = 1 : 0);
	(key == K_LA ? env->keys.k_la = 1 : 0);
	(key == K_RA ? env->keys.k_ra = 1 : 0);
	(key == K_UA ? env->keys.k_ua = 1 : 0);
	(key == K_DA ? env->keys.k_da = 1 : 0);
	(key == K_A ? env->keys.k_a = 1 : 0);
	(key == K_B ? env->keys.k_b = 1 : 0);
	(key == K_C ? env->keys.k_c = 1 : 0);
	(key == K_D ? env->keys.k_d = 1 : 0);
	(key == K_E ? env->keys.k_e = 1 : 0);
	(key == K_F ? env->keys.k_f = 1 : 0);
	(key == K_G ? env->keys.k_g = 1 : 0);
	(key == K_H ? env->keys.k_h = 1 : 0);
	(key == K_I ? env->keys.k_i = 1 : 0);
	(key == K_J ? env->keys.k_j = 1 : 0);
	(key == K_K ? env->keys.k_k = 1 : 0);
	(key == K_L ? env->keys.k_l = 1 : 0);
	(key == K_M ? env->keys.k_m = 1 : 0);
	(key == K_N ? env->keys.k_n = 1 : 0);
	(key == K_O ? env->keys.k_o = 1 : 0);
	(key == K_P ? env->keys.k_p = 1 : 0);
	(key == K_Q ? env->keys.k_q = 1 : 0);
	(key == K_R ? env->keys.k_r = 1 : 0);
	(key == K_S ? env->keys.k_s = 1 : 0);
	(key == K_T ? env->keys.k_t = 1 : 0);
}

static	void	fdf_key_press_2(int key, t_env *env)
{
	(key == K_U ? env->keys.k_u = 1 : 0);
	(key == K_V ? env->keys.k_v = 1 : 0);
	(key == K_W ? env->keys.k_w = 1 : 0);
	(key == K_X ? env->keys.k_x = 1 : 0);
	(key == K_Y ? env->keys.k_y = 1 : 0);
	(key == K_Z ? env->keys.k_z = 1 : 0);
	(key == K_0 ? env->keys.k_0 = 1 : 0);
	(key == K_1 ? env->keys.k_1 = 1 : 0);
	(key == K_2 ? env->keys.k_2 = 1 : 0);
	(key == K_3 ? env->keys.k_3 = 1 : 0);
	(key == K_4 ? env->keys.k_4 = 1 : 0);
	(key == K_5 ? env->keys.k_5 = 1 : 0);
	(key == K_6 ? env->keys.k_6 = 1 : 0);
	(key == K_7 ? env->keys.k_7 = 1 : 0);
	(key == K_8 ? env->keys.k_8 = 1 : 0);
	(key == K_9 ? env->keys.k_9 = 1 : 0);
	(key == K_N0 ? env->keys.k_n0 = 1 : 0);
	(key == K_N1 ? env->keys.k_n1 = 1 : 0);
	(key == K_N2 ? env->keys.k_n2 = 1 : 0);
	(key == K_N3 ? env->keys.k_n3 = 1 : 0);
	(key == K_N4 ? env->keys.k_n4 = 1 : 0);
	(key == K_N5 ? env->keys.k_n5 = 1 : 0);
	(key == K_N6 ? env->keys.k_n6 = 1 : 0);
	(key == K_N7 ? env->keys.k_n7 = 1 : 0);
	(key == K_N8 ? env->keys.k_n8 = 1 : 0);
}

static	void	fdf_key_press_3(int key, t_env *env)
{
	(key == K_N9 ? env->keys.k_n9 = 1 : 0);
	(key == K_NSLA ? env->keys.k_nsla = 1 : 0);
	(key == K_NSTR ? env->keys.k_nstr = 1 : 0);
	(key == K_NMIN ? env->keys.k_nmin = 1 : 0);
	(key == K_NPLU ? env->keys.k_nplu = 1 : 0);
	(key == K_NENT ? env->keys.k_nent = 1 : 0);
	(key == K_NDOT ? env->keys.k_ndot = 1 : 0);
	(key == K_NEQU ? env->keys.k_nequ = 1 : 0);
	(key == K_NDEL ? env->keys.k_ndel = 1 : 0);
	(key == K_HOME ? env->keys.k_home = 1 : 0);
	(key == K_END ? env->keys.k_end = 1 : 0);
	(key == K_PGU ? env->keys.k_pgu = 1 : 0);
	(key == K_PGD ? env->keys.k_pgd = 1 : 0);
	(key == K_DEL ? env->keys.k_del = 1 : 0);
	(key == K_BSP ? env->keys.k_bsp = 1 : 0);
	(key == K_SPC ? env->keys.k_spc = 1 : 0);
	(key == K_LSHI ? env->keys.k_lshi = 1 : 0);
	(key == K_RSHI ? env->keys.k_rshi = 1 : 0);
	(key == K_LCTRL ? env->keys.k_lctrl = 1 : 0);
	(key == K_RCTRL ? env->keys.k_rctrl = 1 : 0);
	(key == K_LOPT ? env->keys.k_lopt = 1 : 0);
	(key == K_ROPT ? env->keys.k_ropt = 1 : 0);
	(key == K_LCMD ? env->keys.k_lcmd = 1 : 0);
	(key == K_RCMD ? env->keys.k_rcmd = 1 : 0);
	(key == K_COM ? env->keys.k_com = 1 : 0);
}

static	void	fdf_key_press_4(int key, t_env *env)
{
	(key == K_DOT ? env->keys.k_dot = 1 : 0);
	(key == K_SLA ? env->keys.k_sla = 1 : 0);
	(key == K_SCOL ? env->keys.k_scol = 1 : 0);
	(key == K_QUO ? env->keys.k_quo = 1 : 0);
	(key == K_LBRA ? env->keys.k_lbra = 1 : 0);
	(key == K_RBRA ? env->keys.k_rbra = 1 : 0);
	(key == K_BSLA ? env->keys.k_bsla = 1 : 0);
	(key == K_DASH ? env->keys.k_dash = 1 : 0);
	(key == K_EQU ? env->keys.k_equ = 1 : 0);
	(key == K_APO ? env->keys.k_apo = 1 : 0);
	(key == K_TAB ? env->keys.k_tab = 1 : 0);
	(key == K_CAPS ? env->keys.k_caps = 1 : 0);
	(key == K_RET ? env->keys.k_ret = 1 : 0);
	(key == K_FN ? env->keys.k_fn = 1 : 0);
	(key == K_F1 ? env->keys.k_f1 = 1 : 0);
	(key == K_F2 ? env->keys.k_f2 = 1 : 0);
	(key == K_F3 ? env->keys.k_f3 = 1 : 0);
	(key == K_F4 ? env->keys.k_f4 = 1 : 0);
	(key == K_F5 ? env->keys.k_f5 = 1 : 0);
	(key == K_F6 ? env->keys.k_f6 = 1 : 0);
	(key == K_F7 ? env->keys.k_f7 = 1 : 0);
	(key == K_F8 ? env->keys.k_f8 = 1 : 0);
	(key == K_F9 ? env->keys.k_f9 = 1 : 0);
	(key == K_F10 ? env->keys.k_f10 = 1 : 0);
	(key == K_F11 ? env->keys.k_f11 = 1 : 0);
}

int				fdf_key_press(int key, t_env *env)
{
	(key == K_F12 ? env->keys.k_f12 = 1 : 0);
	(key == K_F13 ? env->keys.k_f13 = 1 : 0);
	(key == K_F14 ? env->keys.k_f14 = 1 : 0);
	(key == K_F15 ? env->keys.k_f15 = 1 : 0);
	(key == K_F16 ? env->keys.k_f16 = 1 : 0);
	(key == K_F17 ? env->keys.k_f17 = 1 : 0);
	(key == K_F18 ? env->keys.k_f18 = 1 : 0);
	(key == K_F19 ? env->keys.k_f19 = 1 : 0);
	fdf_key_press_1(key, env);
	fdf_key_press_2(key, env);
	fdf_key_press_3(key, env);
	fdf_key_press_4(key, env);
	return (0);
}
