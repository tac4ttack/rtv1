#include "rtv1.h"

int		mlx_mouse_events(int btn, int x, int y, t_env *e)
{
//	instruction du dessous juste pour faire fermer sa gueule a clang
	btn = btn - 1 + 1;
	e->run = 1;
	e->mou_x = x;
	e->mou_y = y;
	printf("toto");
	return (0);
}
