#include "rtv1.h"

void		set_hooks(t_env *e)
{
	mlx_hook(e->win, DESTROYNOTIFY, KEYRELEASEMASK, quit, e);
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, mlx_key_press, e);
	mlx_hook(e->win, KEYRELEASE, KEYRELEASEMASK, mlx_key_release, e);
	mlx_mouse_hook(e->win, mlx_mouse_events, e);
	mlx_loop_hook(e->mlx, mlx_main_loop, e);
	mlx_loop(e->mlx);
}

t_object	*load_scene(t_env *e)
{
	t_object	*res;
	if (!(res = malloc(sizeof(t_object) * 4)))
		s_error("\x1b[2;31mCan't create scene array\x1b[0m");
	res[0]
}

void		frame_init(t_env *e)
{
	int		bpp;
	int		row;
	int		endian;

	if (!(e->frame = malloc(sizeof(t_frame))))
		s_error("\x1b[2;31mCan't initialize the frame\x1b[0m");
	e->frame->w = e->win_w;
	e->frame->h = e->win_h;
//	a proteger les 2 instructions en dessous
	if (!(e->frame->ptr = mlx_new_image(e->mlx, e->frame->w, e->frame->h)))
		s_error("\x1b[2;31mCan't create new mlx image\x1b[0m");
	if (!(e->frame->pix = mlx_get_data_addr(e->frame->ptr, \
							&(bpp), &(row), &(endian))))
		s_error("\x1b[2;31mCan't create get image address\x1b[0m");
	e->frame->bpp = bpp;
	e->frame->row = row;
	e->frame->endian = endian;
//	e->scene = load_scene(t_env *e);
}

void		init(t_env *e)
{
	e->debug = DBUG;
	e->win_w = WIDTH;
	e->win_h = HEIGHT;
	e->cen_x = e->win_w / 2;
	e->cen_y = e->win_h / 2;
	e->mou_x = 0;
	e->mou_y = 0;
	e->mvx = 0;
	e->mvy = 0;
	e->mvz = 0;	
	e->gpu = IS_GPU;

	e->run = 1;

	ft_bzero(&e->keys, sizeof(t_key));
	if (!(e->mlx = mlx_init()))
		s_error("\x1b[2;31mError can't initialize minilibx\x1b[0m");
	if (!(e->win = mlx_new_window(e->mlx, e->win_w, e->win_h, "RTv1")))
		s_error("\x1b[2;31mError minilibx window creation failed\x1b[0m");
	frame_init(e);
	if (opencl_init(e) != 0)
	{
		e->gpu = 0;
		opencl_init(e);
	}
	set_hooks(e);
}
