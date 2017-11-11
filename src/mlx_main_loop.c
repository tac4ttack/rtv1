#include "rtv1.h"

void	display_hud(t_env *e)
{
	char *mvtx;
	char *mvty;
	char *mvtz;
	char *bloom;

	mvtx = ft_ftoa(e->cameras[0].pos.x + e->mvt.x);
	mvty = ft_ftoa(e->cameras[0].pos.y + e->mvt.y);
	mvtz = ft_ftoa(e->cameras[0].pos.z + e->mvt.z);
	bloom = ft_ftoa(e->param.bloom);
	mlx_string_put(e->mlx, e->win, 10, 10, 0x00ffffff, mvtx);
	mlx_string_put(e->mlx, e->win, 10, 25, 0x00ffffff, mvty);
	mlx_string_put(e->mlx, e->win, 10, 40, 0x00ffffff, mvtz);
	mlx_string_put(e->mlx, e->win, 10, 55, 0x00ffffff, bloom);
	free(mvtx);
	free(mvty);
	free(mvtz);
	free(bloom);
}

void	refresh(t_env *e)
{
	if (e)
	{
		mlx_clear_window(e->mlx, e->win);
		draw(e);
		mlx_put_image_to_window(e->mlx, e->win, e->frame->ptr, 0, 0);
	//	display_hud(e);
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
