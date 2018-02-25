#include "rtv1.h"

void			mlx_keyboard_repeated(t_env *e)
{
	if (!e)
		exit(EXIT_FAILURE);
	(KP_ESC ? quit(e) : 0);
	if (KP_W || KP_S || KP_A || KP_D || KP_C || KP_SPC || \
		KP_DA || KP_UA || KP_LA || KP_RA || KP_Z)
		ui_cam(e);
	if (KP_I || KP_J || KP_K || KP_L || KP_U || KP_O || \
		KP_N4 || KP_N6 || KP_N8 || KP_N5 || KP_N7 || KP_N9)
		ui_obj(e);
	if (KP_T)
		printf("type : %d, id ; %d, x : %d, y : %d\n", e->target_obj.type, e->target_obj.id, e->scene->mou_x, e->scene->mou_y);
	if (KP_NPLU)
		e->scene->depth++; // WIP
	if (KP_NMIN)
		(e->scene->depth > 0 ? e->scene->depth-- : 0); // WIP
//	if (KP_NSTR)
//		e->scene->refra++;
	opencl_allocate_scene_memory(e);
}
