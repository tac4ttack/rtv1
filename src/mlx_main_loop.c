#include "rtv1.h"

void	refresh(t_env *e)
{
	if (e)
	{
		mlx_clear_window(e->mlx, e->win);
		draw(e);
		mlx_put_image_to_window(e->mlx, e->win, e->scene->ptr, 0, 0);
		mlx_string_put(e->mlx, e->win, 10, 10, 0x00ffffff, ft_ftoa(e->mvx));
		mlx_string_put(e->mlx, e->win, 10, 25, 0x00ffffff, ft_ftoa(e->mvy));
		mlx_string_put(e->mlx, e->win, 10, 40, 0x00ffffff, ft_ftoa(e->mvz));
		e->run = 0;
	}
}

int		mlx_main_loop(t_env *e)
{
	if (e)
	{
		mlx_keyboard_repeated(e);
		mlx_mouse_get_pos(e->win, &e->mou_x, &e->mou_y);
		refresh(e);
	//	quit(e);
	}
	return (0);
}
