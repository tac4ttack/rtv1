#include "rtv1.h"

void	display_hud(t_env *e)
{
	char *mvtx;
	char *mvty;
	char *mvtz;
	
	mvtx = ft_ftoa(e->cameras[0].pos.x + e->param.mvt.x);
	mvty = ft_ftoa(e->cameras[0].pos.y + e->param.mvt.y);
	mvtz = ft_ftoa(e->cameras[0].pos.z + e->param.mvt.z);
	mlx_string_put(e->mlx, e->win, 10, 10, 0x00ffffff, mvtx);
	mlx_string_put(e->mlx, e->win, 10, 25, 0x00ffffff, mvty);
	mlx_string_put(e->mlx, e->win, 10, 40, 0x00ffffff, mvtz);
	mlx_string_put(e->mlx, e->win, 10, 70, 0x00ffffff, ft_ftoa(e->cameras[0].pitch));
	mlx_string_put(e->mlx, e->win, 10, 85, 0x00ffffff, ft_ftoa(e->cameras[0].yaw));
	mlx_string_put(e->mlx, e->win, 10, 100, 0x00ffffff, ft_ftoa(e->cameras[0].roll));
	free(mvtx);
	free(mvty);
	free(mvtz);
}

void	refresh(t_env *e)
{
	if (e)
	{
			
		mlx_clear_window(e->mlx, e->win);

		draw(e);

		mlx_put_image_to_window(e->mlx, e->win, e->frame->ptr, 0, 0);
		display_hud(e);
	//	e->run = 0;
	}
}

int		mlx_main_loop(t_env *e)
{
	if (e)
	{
		mlx_keyboard_repeated(e);
		//printf("type : %d, id ; %d, x : %d, y : %d\n", e->param.target_obj.type, e->param.target_obj.id, e->mou_x, e->mou_y);
		refresh(e);
	//	quit(e);
	}
	return (0);
}
