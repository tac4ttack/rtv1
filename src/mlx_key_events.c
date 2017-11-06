#include "rtv1.h"

void	reset_cam_pos(t_env *e)
{
	if (e)
	{
		e->mvt.x = 0;
		e->mvt.y = 0;
		e->mvt.z = 0;
		e->param.bloom = 1.80;
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
	(KP_NPLU ? e->param.bloom += 0.1 : 0);
	(KP_NMIN ? e->param.bloom -= 0.1 : 0);
	if (KP_N4 || KP_N6 || KP_N8 || KP_N5 || KP_N7 || KP_N9)
	{
		(KP_N4 ? e->lights[0].pos.x -= 0.1 : 0);
		(KP_N6 ? e->lights[0].pos.x += 0.1 : 0);
		(KP_N8 ? e->lights[0].pos.y -= 0.1 : 0);
		(KP_N5 ? e->lights[0].pos.y += 0.1 : 0);
		(KP_N7 ? e->lights[0].pos.z -= 0.1 : 0);
		(KP_N9 ? e->lights[0].pos.z += 0.1 : 0);
		opencl_allocate_scene_memory(e);
	}
	(KP_SPC ? e->mvt.y -= 0.1 : 0);
	(KP_C ? e->mvt.y += 0.1 : 0);
	(KP_R ? reset_cam_pos(e) : 0);
}
