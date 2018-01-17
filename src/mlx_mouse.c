#include "rtv1.h"

int		mlx_mouse_events(int btn, int x, int y, t_env *e)
{
	if (btn == 1)
	{
		e->run = 1; //useless pitetre a virer
		e->param.mou_x = x;
		e->param.mou_y = y;
	}
	return (0);
}
