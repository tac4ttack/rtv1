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
	//(KP_S ? e->param.mvt.z -= 1 : 0);
	//(KP_A ? e->param.mvt.x -= 1 : 0);
	//(KP_D ? e->param.mvt.x += 1 : 0);
	(KP_SPC ? e->param.mvt.y += 1 : 0);
	//(KP_C ? e->param.mvt.y -= 1 : 0);	
//	(KP_R ? reset_cam_pos(e) : 0);
	(KP_NPLU ? e->param.bloom += 0.1 : 0);
	(KP_NMIN ? e->param.bloom -= 0.1 : 0);
	if (KP_R)
		get_activeobj(e);
	if (KP_N4 || KP_N6 || KP_N8 || KP_N5 || KP_N7 || KP_N9 \
		|| KP_I || KP_K || KP_J || KP_L || KP_U || KP_O || KP_LA || KP_UA || KP_RA || KP_DA || KP_W || KP_D || KP_C || KP_A || KP_S)
	{
		if (KP_W)
			e->cameras[0].pos = add_cl_float(rotcam(e->cameras[0].dir, e->cameras[0].pitch * DEG2RAD, e->cameras[0].yaw * DEG2RAD), e->cameras[0].pos);
		if (KP_S)
			e->cameras[0].pos = sub_cl_float(e->cameras[0].pos, rotcam(e->cameras[0].dir, e->cameras[0].pitch * DEG2RAD, e->cameras[0].yaw * DEG2RAD));
		if (KP_C)
			e->cameras[0].pos = add_cl_float(rotcam(e->cameras[0].dir, (e->cameras[0].pitch + 90) * DEG2RAD, e->cameras[0].yaw * DEG2RAD), e->cameras[0].pos);
		if (KP_D)
			e->cameras[0].pos = add_cl_float(rotcam(e->cameras[0].dir, e->cameras[0].pitch * DEG2RAD, (e->cameras[0].yaw + 90) * DEG2RAD), e->cameras[0].pos);
		if (KP_A)
			e->cameras[0].pos = add_cl_float(rotcam(e->cameras[0].dir, e->cameras[0].pitch * DEG2RAD, (e->cameras[0].yaw - 90) * DEG2RAD), e->cameras[0].pos);

		(KP_DA ? e->cameras[0].pitch += 2 : 0);
		if (e->cameras[0].pitch == 360)
			e->cameras[0].pitch = 0;
		(KP_UA ? e->cameras[0].pitch -= 2 : 0);
		if (e->cameras[0].pitch == -1)
			e->cameras[0].pitch = 359;
		(KP_LA ? e->cameras[0].yaw -= 2 : 0);
		if (e->cameras[0].yaw == 360)
			e->cameras[0].yaw = 0;
		(KP_RA ? e->cameras[0].yaw += 2 : 0);
		if (e->cameras[0].yaw == -1)
			e->cameras[0].yaw = 359;
		if (NCYL > 0)
		{
			if (KP_I)
			{
				e->cylinders[0].dir = rotx(e->cylinders[0].dir, 1 * DEG2RAD);
			}
			if (KP_K)
			{
				e->cylinders[0].dir = rotx(e->cylinders[0].dir, -1 * DEG2RAD);
			}
			if (KP_J)
			{
				e->cylinders[0].dir = roty(e->cylinders[0].dir, 1 * DEG2RAD);
			}
			if (KP_L)
			{
				e->cylinders[0].dir = roty(e->cylinders[0].dir, -1 * DEG2RAD);
			}
			if (KP_U)
			{
				e->cylinders[0].dir = rotz(e->cylinders[0].dir, 1 * DEG2RAD);
			}
			if (KP_O)
			{
				e->cylinders[0].dir = rotz(e->cylinders[0].dir, -1 * DEG2RAD);
			}
		}
		(KP_N4 ? e->lights[0].pos.x -= 0.1 : 0);
		(KP_N6 ? e->lights[0].pos.x += 0.1 : 0);
		(KP_N8 ? e->lights[0].pos.y -= 0.1 : 0);
		(KP_N5 ? e->lights[0].pos.y += 0.1 : 0);
		(KP_N7 ? e->lights[0].pos.z -= 0.1 : 0);
		(KP_N9 ? e->lights[0].pos.z += 0.1 : 0);
		if (KP_Z)
			e->param.active_cam = (e->param.active_cam + 1 < NCAM ? e->param.active_cam + 1 : 0);
		opencl_allocate_scene_memory(e);
	}
}
