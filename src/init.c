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

t_object	*load_scene(void)
{
	t_object	*res;
	if (!(res = malloc(sizeof(t_object) * 4)))
		s_error("\x1b[2;31mCan't create scene array\x1b[0m");
	
	//camera
	ft_bzero(&res[0], sizeof(t_object));
	res[0].type = 0;
	res[0].id = 0;
	res[0].cam.pos.x = 0;
	res[0].cam.pos.y = 0;
	res[0].cam.pos.z = 0;
	res[0].cam.dir.x = 0;
	res[0].cam.dir.y = 0;
	res[0].cam.dir.z = 1;
	res[0].cam.hor.x = 0.6;
	res[0].cam.hor.y = 0;
	res[0].cam.hor.z = 0;
	res[0].cam.ver.x = 0;
	res[0].cam.ver.y = 0.6;
	res[0].cam.ver.z = 0;

	//plane
	ft_bzero(&res[1], sizeof(t_object));
	res[1].type = 4;
	res[1].id = 1;
	res[1].plane.pos.x = 0;
	res[1].plane.pos.y = 0;
	res[1].plane.pos.z = 0;
	res[1].plane.normale.x = 0;
	res[1].plane.normale.y = 1;
	res[1].plane.normale.z = 0;
	res[1].plane.color = 0x00ff0000;

	//sphere 1
	ft_bzero(&res[2], sizeof(t_object));
	res[2].type = 5;
	res[2].id = 2;
	res[2].sphere.pos.x = 0;
	res[2].sphere.pos.y = 0;
	res[2].sphere.pos.x = 0;
//	res[2].sphere.dir.x = 0;
//	res[2].sphere.dir.y = 0;
//	res[2].sphere.dir.z = 0;
	res[2].sphere.radius = 5;
	res[2].sphere.color = 0x0000ff00;

	//sphere 2
	ft_bzero(&res[3], sizeof(t_object));
	res[3].type = 5;
	res[3].id = 3;
	res[3].sphere.pos.x = 0;
	res[3].sphere.pos.y = 0;
	res[3].sphere.pos.x = 0;
//	res[3].sphere.dir.x = 0;
//	res[3].sphere.dir.y = 0;
//	res[3].sphere.dir.z = 0;
	res[3].sphere.radius = 10;
	res[3].sphere.color = 0x000000ff;

	return (res);
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
	if (!(e->frame->ptr = mlx_new_image(e->mlx, e->frame->w, e->frame->h)))
		s_error("\x1b[2;31mCan't create new mlx image\x1b[0m");
	if (!(e->frame->pix = mlx_get_data_addr(e->frame->ptr, \
							&(bpp), &(row), &(endian))))
		s_error("\x1b[2;31mCan't create get image address\x1b[0m");
	e->frame->bpp = bpp;
	e->frame->row = row;
	e->frame->endian = endian;
	e->scene = load_scene();
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
	e->mvt.x = 0.0;
	e->mvt.y = 0.0;
	e->mvt.z = 0.0;
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
