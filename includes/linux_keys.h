/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_keys.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 23:28:58 by fmessina          #+#    #+#             */
/*   Updated: 2017/09/14 19:42:46 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINUX_KEYS_H
# define LINUX_KEYS_H

typedef	struct	s_key
{
	int			k_esc;
	int			k_la;
	int			k_ra;
	int			k_ua;
	int			k_da;
	int			k_a;
	int			k_b;
	int			k_c;
	int			k_d;
	int			k_e;
	int			k_f;
	int			k_g;
	int			k_h;
	int			k_i;
	int			k_j;
	int			k_k;
	int			k_l;
	int			k_m;
	int			k_n;
	int			k_o;
	int			k_p;
	int			k_q;
	int			k_r;
	int			k_s;
	int			k_t;
	int			k_u;
	int			k_v;
	int			k_w;
	int			k_x;
	int			k_y;
	int			k_z;
	int			k_0;
	int			k_1;
	int			k_2;
	int			k_3;
	int			k_4;
	int			k_5;
	int			k_6;
	int			k_7;
	int			k_8;
	int			k_9;
	int			k_n0;
	int			k_n1;
	int			k_n2;
	int			k_n3;
	int			k_n4;
	int			k_n5;
	int			k_n6;
	int			k_n7;
	int			k_n8;
	int			k_n9;
	int			k_nsla;
	int			k_nstr;
	int			k_nmin;
	int			k_nplu;
	int			k_nent;
	int			k_ndot;
	int			k_ndel;
	int			k_home;
	int			k_end;
	int			k_pgu;
	int			k_pgd;
	int			k_del;
	int			k_bsp;
	int			k_spc;
	int			k_lshi;
	int			k_rshi;
	int			k_lctrl;
	int			k_rctrl;
	int			k_lopt;
	int			k_ropt;
	int			k_com;
	int			k_dot;
	int			k_sla;
	int			k_scol;
	int			k_quo;
	int			k_lbra;
	int			k_rbra;
	int			k_bsla;
	int			k_dash;
	int			k_equ;
	int			k_apo;
	int			k_tab;
	int			k_caps;
	int			k_ret;
	int			k_fn;
	int			k_f1;
	int			k_f2;
	int			k_f3;
	int			k_f4;
	int			k_f5;
	int			k_f6;
	int			k_f7;
	int			k_f8;
	int			k_f9;
	int			k_f10;
	int			k_f11;
	int			k_f12;
	int			k_f13;
	int			k_f14;
	int			k_f15;
	int			k_f16;
	int			k_f17;
	int			k_f18;
	int			k_f19;
}				t_key;

/*
****	MACOS KEYS DEFINE	****
*/
# define K_ESC						65307
# define K_LA						65361
# define K_RA						65363
# define K_UA						65362
# define K_DA						65364
# define K_A						97
# define K_B						98
# define K_C						99
# define K_D						100
# define K_E						101
# define K_F						102
# define K_G						103
# define K_H						104
# define K_I						105
# define K_J						106
# define K_K						107
# define K_L						108
# define K_M						109
# define K_N						110
# define K_O						111
# define K_P						112
# define K_Q						113
# define K_R						114
# define K_S						115
# define K_T						116
# define K_U						117
# define K_V						118
# define K_W						119
# define K_X						120
# define K_Y						121
# define K_Z						122
# define K_0						48
# define K_1						49
# define K_2						50
# define K_3						51
# define K_4						52
# define K_5						53
# define K_6						54
# define K_7						55
# define K_8						56
# define K_9						57
# define K_N0						65438
# define K_N1						65436
# define K_N2						65433
# define K_N3						65435
# define K_N4						65430
# define K_N5						65437
# define K_N6						65432
# define K_N7						65429
# define K_N8						65431
# define K_N9						65434
# define K_NSLA						65455
# define K_NSTR						65450
# define K_NMIN						65453
# define K_NPLU						65451
# define K_NENT						65421
# define K_NDOT						65439
# define K_NDEL						65439
# define K_HOME						65360
# define K_END						65367
# define K_PGU						65365
# define K_PGD						65366
# define K_DEL						65535
# define K_BSP						65288
# define K_SPC						32
# define K_LSHI						65505
# define K_RSHI						65506
# define K_LCTRL					65507
# define K_RCTRL					65508
# define K_LOPT						65513
# define K_ROPT						65514
# define K_COM						44
# define K_DOT						46
# define K_SLA						47
# define K_SCOL						52
# define K_QUO						39
# define K_LBRA						91
# define K_RBRA						93
# define K_BSLA						92
# define K_DASH						45
# define K_EQU						61
# define K_APO						96
# define K_TAB						65289
# define K_CAPS						65509
# define K_RET						65293
# define K_FN						65383
# define K_F1						65470
# define K_F2						65471
# define K_F3						65472
# define K_F4						65473
# define K_F5						65474
# define K_F6						65475
# define K_F7						65476
# define K_F8						65477
# define K_F9						65478
# define K_F10						65479
# define K_F11						65480
# define K_F12						65481
# define K_F13						105
# define K_F14						107
# define K_F15						113
# define K_F16						106
# define K_F17						64
# define K_F18						79
# define K_F19						80

# define KP_ESC						e->keys.k_esc
# define KP_LA						e->keys.k_la
# define KP_RA						e->keys.k_ra
# define KP_UA						e->keys.k_ua
# define KP_DA						e->keys.k_da
# define KP_A						e->keys.k_a
# define KP_B						e->keys.k_b
# define KP_C						e->keys.k_c
# define KP_D						e->keys.k_d
# define KP_E						e->keys.k_e
# define KP_F						e->keys.k_f
# define KP_G						e->keys.k_g
# define KP_H						e->keys.k_h
# define KP_I						e->keys.k_i
# define KP_J						e->keys.k_j
# define KP_K						e->keys.k_k
# define KP_L						e->keys.k_l
# define KP_M						e->keys.k_m
# define KP_N						e->keys.k_n
# define KP_O						e->keys.k_o
# define KP_P						e->keys.k_p
# define KP_Q						e->keys.k_q
# define KP_R						e->keys.k_r
# define KP_S						e->keys.k_s
# define KP_T						e->keys.k_t
# define KP_U						e->keys.k_u
# define KP_V						e->keys.k_v
# define KP_W						e->keys.k_w
# define KP_X						e->keys.k_x
# define KP_Y						e->keys.k_y
# define KP_Z						e->keys.k_z
# define KP_0						e->keys.k_0
# define KP_1						e->keys.k_1
# define KP_2						e->keys.k_2
# define KP_3						e->keys.k_3
# define KP_4						e->keys.k_4
# define KP_5						e->keys.k_5
# define KP_6						e->keys.k_6
# define KP_7						e->keys.k_7
# define KP_8						e->keys.k_8
# define KP_9						e->keys.k_9
# define KP_N0						e->keys.k_n0
# define KP_N1						e->keys.k_n1
# define KP_N2						e->keys.k_n2
# define KP_N3						e->keys.k_n3
# define KP_N4						e->keys.k_n4
# define KP_N5						e->keys.k_n5
# define KP_N6						e->keys.k_n6
# define KP_N7						e->keys.k_n7
# define KP_N8						e->keys.k_n8
# define KP_N9						e->keys.k_n9
# define KP_NSLA					e->keys.k_nsla
# define KP_NSTR					e->keys.k_nstr
# define KP_NMIN					e->keys.k_nmin
# define KP_NPLU					e->keys.k_nplu
# define KP_NENT					e->keys.k_nent
# define KP_NDOT					e->keys.k_ndot
# define KP_NDEL					e->keys.k_ndel
# define KP_HOME					e->keys.k_home
# define KP_END						e->keys.k_end
# define KP_PGU						e->keys.k_pgu
# define KP_PGD						e->keys.k_pgd
# define KP_DEL						e->keys.k_del
# define KP_BSP						e->keys.k_bsp
# define KP_SPC						e->keys.k_spc
# define KP_LSHI					e->keys.k_lshi
# define KP_RSHI					e->keys.k_rshi
# define KP_LCTRL					e->keys.k_lctrl
# define KP_RCTRL					e->keys.k_rctrl
# define KP_LOPT					e->keys.k_lopt
# define KP_ROPT					e->keys.k_ropt
# define KP_COM						e->keys.k_com
# define KP_DOT						e->keys.k_dot
# define KP_SLA						e->keys.k_sla
# define KP_SCOL					e->keys.k_scol
# define KP_QUO						e->keys.k_quo
# define KP_LBRA					e->keys.k_lbra
# define KP_RBRA					e->keys.k_rbra
# define KP_BSLA					e->keys.k_bsla
# define KP_DASH					e->keys.k_dash
# define KP_EQU						e->keys.k_equ
# define KP_APO						e->keys.k_apo
# define KP_TAB						e->keys.k_tab
# define KP_CAP						e->keys.k_cap
# define KP_RET						e->keys.k_ret
# define KP_FN						e->keys.k_fn
# define KP_F1						e->keys.k_f1
# define KP_F2						e->keys.k_f2
# define KP_F3						e->keys.k_f3
# define KP_F4						e->keys.k_f4
# define KP_F5						e->keys.k_f5
# define KP_F6						e->keys.k_f6
# define KP_F7						e->keys.k_f7
# define KP_F8						e->keys.k_f8
# define KP_F9						e->keys.k_f9
# define KP_F10						e->keys.k_f10
# define KP_F11						e->keys.k_f11
# define KP_F12						e->keys.k_f12
# define KP_F13						e->keys.k_f13
# define KP_F14						e->keys.k_f14
# define KP_F15						e->keys.k_f15
# define KP_F16						e->keys.k_f16
# define KP_F17						e->keys.k_f17
# define KP_F18						e->keys.k_f18
# define KP_F19						e->keys.k_f19

#endif
