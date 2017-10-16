#include "rtv1.h"

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
}
