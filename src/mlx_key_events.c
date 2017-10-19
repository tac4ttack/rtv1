#include "rtv1.h"

void	reset_cam_pos(t_env *e)
{
	if (e)
	{
		e->mvt.x = 0;
		e->mvt.y = 0;
		e->mvt.z = 0;
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
	(KP_W ? e->mvt.z += 0.1 : 0);
	(KP_S ? e->mvt.z -= 0.1 : 0);
	(KP_A ? e->mvt.x -= 0.1 : 0);
	(KP_D ? e->mvt.x += 0.1 : 0);
	(KP_SPC ? e->mvt.y -= 0.1 : 0);
	(KP_C ? e->mvt.y += 0.1 : 0);
	(KP_R ? reset_cam_pos(e) : 0);
}
