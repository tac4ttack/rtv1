#include "rtv1.h"

void	reset_cam_pos(t_env *e)
{
	if (e)
	{
		e->mvx = 0;
		e->mvy = 0;
		e->mvz = 0;
//		e->rtx = 0;
//		e->rty = 0;
//		e->rtz = 0;
	}
}

void			mlx_keyboard_repeated(t_env *e)
{
	if (!e)
		exit(EXIT_FAILURE);
	(KP_ESC ? quit(e) : 0);
	(KP_Q ? quit(e) : 0);
	(KP_W ? e->mvz += 0.1 : 0);
	(KP_S ? e->mvz -= 0.1 : 0);
	(KP_A ? e->mvx -= 0.1 : 0);
	(KP_D ? e->mvx += 0.1 : 0);
	(KP_SPC ? e->mvy -= 0.1 : 0);
	(KP_C ? e->mvy += 0.1 : 0);
	(KP_R ? reset_cam_pos(e) : 0);
}
