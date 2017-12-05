#include "rtv1.h"

void	reset_cam_pos(t_env *e)
{
	if (e)
	{
		e->param.mvt.x = 0;
		e->param.mvt.y = 0;
		e->param.mvt.z = 0;
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
	(KP_W ? e->param.mvt.z += 0.1 : 0);
	(KP_S ? e->param.mvt.z -= 0.1 : 0);
	(KP_A ? e->param.mvt.x -= 0.1 : 0);
	(KP_D ? e->param.mvt.x += 0.1 : 0);
	(KP_SPC ? e->param.mvt.y += 0.1 : 0);
	(KP_C ? e->param.mvt.y -= 0.1 : 0);
	(KP_R ? reset_cam_pos(e) : 0);
	(KP_NPLU ? e->param.bloom += 0.1 : 0);
	(KP_NMIN ? e->param.bloom -= 0.1 : 0);
	if (KP_N4 || KP_N6 || KP_N8 || KP_N5 || KP_N7 || KP_N9 \
		|| KP_I || KP_K || KP_J || KP_L || KP_U || KP_O)
	{
//		(KP_I ? e->cameras[0].dir.y += 0.01 : 0);
//		(KP_K ? e->cameras[0].dir.y -= 0.01 : 0);
//		(KP_J ? e->cameras[0].dir.x -= 0.01 : 0);
//		(KP_L ? e->cameras[0].dir.x += 0.01 : 0);
//		(KP_U ? e->cameras[0].dir.z += 0.01 : 0);
//		(KP_O ? e->cameras[0].dir.z -= 0.01 : 0);
		(KP_N4 ? e->lights[0].pos.x -= 0.1 : 0);
		(KP_N6 ? e->lights[0].pos.x += 0.1 : 0);
		(KP_N8 ? e->lights[0].pos.y -= 0.1 : 0);
		(KP_N5 ? e->lights[0].pos.y += 0.1 : 0);
		(KP_N7 ? e->lights[0].pos.z -= 0.1 : 0);
		(KP_N9 ? e->lights[0].pos.z += 0.1 : 0);
		opencl_allocate_scene_memory(e);
	}
}
