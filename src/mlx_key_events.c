#include "rtv1.h"

void			mlx_keyboard_repeated(t_env *e)
{
	if (!e)
		exit(EXIT_FAILURE);
	(KP_ESC ? quit(e) : 0);
	if (KP_W || KP_S || KP_A || KP_D || KP_C || KP_SPC)
	{
		(KP_SPC ? e->param.mvt.y += 1 : 0);
		if (KP_W)
			e->cameras[0].pos = add_cl_float(rotcam(e->cameras[0].dir, e->cameras[0].pitch * DEG2RAD, e->cameras[0].yaw * DEG2RAD), e->cameras[0].pos);
		if (KP_S)
			e->cameras[0].pos = sub_cl_float(e->cameras[0].pos, rotcam(e->cameras[0].dir, e->cameras[0].pitch * DEG2RAD, e->cameras[0].yaw * DEG2RAD));
		if (KP_C)
			e->cameras[0].pos = add_cl_float(rotcam(e->cameras[0].dir, (e->cameras[0].pitch + 90) * DEG2RAD, e->cameras[0].yaw * DEG2RAD), e->cameras[0].pos);
		if (KP_D)
			e->cameras[0].pos = add_cl_float(rotcam(e->cameras[0].dir, 0, (e->cameras[0].yaw + 90) * DEG2RAD), e->cameras[0].pos);
		if (KP_A)
			e->cameras[0].pos = add_cl_float(rotcam(e->cameras[0].dir, 0, (e->cameras[0].yaw - 90) * DEG2RAD), e->cameras[0].pos);
	}
	if (KP_DA || KP_UA || KP_LA || KP_RA)
	{
		(KP_DA ? ACTIVECAM.pitch += 2 : 0);
		if (ACTIVECAM.pitch == 360)
			ACTIVECAM.pitch = 0;
		(KP_UA ? ACTIVECAM.pitch -= 2 : 0);
		if (ACTIVECAM.pitch == -1)
			ACTIVECAM.pitch = 359;
		(KP_LA ? ACTIVECAM.yaw -= 2 : 0);
		if (ACTIVECAM.yaw == 360)
			ACTIVECAM.yaw = 0;
		(KP_RA ? ACTIVECAM.yaw += 2 : 0);
		if (ACTIVECAM.yaw == -1)
			ACTIVECAM.yaw = 359;
	}
	if (KP_Z)
		e->param.active_cam = (e->param.active_cam + 1 < NCAM ? e->param.active_cam + 1 : 0);
	if (KP_I || KP_J || KP_K || KP_L || KP_U || KP_O || \
		KP_N4 || KP_N6 || KP_N8 || KP_N5 || KP_N7 || KP_N9)
		obj_ui(e);
	if (KP_T)
		printf("type : %d, id ; %d, x : %d, y : %d\n", e->param.target_obj.type, e->param.target_obj.id, e->param.mou_x, e->param.mou_y);
	opencl_allocate_scene_memory(e);
}
