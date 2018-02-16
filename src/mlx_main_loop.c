#include "rtv1.h"

int		mlx_main_loop(t_env *e)
{
	if (e)
	{
		mlx_keyboard_repeated(e);
		mlx_clear_window(e->mlx, e->win);
		draw(e);
		mlx_put_image_to_window(e->mlx, e->win, e->frame->ptr, 0, 0);
		display_hud(e);
	}
	return (0);
}
