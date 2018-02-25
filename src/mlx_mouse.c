#include "rtv1.h"

int		mlx_mouse_events(int btn, int x, int y, t_env *e)
{
	if (btn == 1)
	{
		e->run = 1;
		e->scene->mou_x = x; // WIP
		e->scene->mou_y = y; // WIP
	}
	return (0);
}
