#include "rtv1.h"

void	refresh(t_env *e)
{
	if (e)
	{
		draw(e);
	//	ft_bzero(e->scene->pix, (e->sce_w * e->sce_h));
		mlx_put_image_to_window(e->mlx, e->win, e->scene->ptr, 0, 0);
		
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
