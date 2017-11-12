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

void	load_scene(t_env *e)
{
	NCAM = 1;
	NCON = 1;
	NCYL = 1;
	NLIG = 2;
	NPLA = 1;
	NSPH = 2;

	if (NCAM > 0)
	{
		if (!(e->cameras = malloc(sizeof(t_cam) * NCAM)))
			s_error("\x1b[2;31mCan't create cameras array\x1b[0m", e);
	}
	else
		e->cameras = NULL;
	if (NCON > 0)
	{
		if (!(e->cones = malloc(sizeof(t_cone) * NCON)))
			s_error("\x1b[2;31mCan't create cones array\x1b[0m", e);
	}
	else
		e->cones = NULL;
	if (NCYL > 0)
	{
		if (!(e->cylinders = malloc(sizeof(t_cylinder) * NCYL)))
			s_error("\x1b[2;31mCan't create cylinders array\x1b[0m", e);
	}
	else
		e->cylinders = NULL;
	if (NLIG > 0)
	{	
		if (!(e->lights = malloc(sizeof(t_light) * NLIG)))
			s_error("\x1b[2;31mCan't create lights array\x1b[0m", e);
	}
	else
		e->lights = NULL;
	if (NPLA > 0)
	{
		if (!(e->planes = malloc(sizeof(t_plane) * NPLA)))
			s_error("\x1b[2;31mCan't create planes array\x1b[0m", e);
	}
	else
		e->planes = NULL;
	if (NSPH > 0)
	{
		if (!(e->spheres = malloc(sizeof(t_sphere) * NSPH)))
			s_error("\x1b[2;31mCan't create spheres array\x1b[0m", e);
	}
	else
		e->spheres = NULL;

//	REMPLISSAGE MANOUEL AIE CARAMBA
	//camera
	ft_bzero(&e->cameras[0], sizeof(t_cam));
	e->cameras[0].pos.x = 0;
	e->cameras[0].pos.y = -5;
	e->cameras[0].pos.z = -10;
	e->cameras[0].dir.x = 2;
	e->cameras[0].dir.y = 0;
	e->cameras[0].dir.z = 1;
	e->cameras[0].hor.x = 0.6;
	e->cameras[0].hor.y = 0;
	e->cameras[0].hor.z = 0;
	e->cameras[0].ver.x = 0;
	e->cameras[0].ver.y = 0.6;
	e->cameras[0].ver.z = 0;

	//plane 1
	ft_bzero(&e->planes[0], sizeof(t_plane));
	e->planes[0].pos.x = 0;
	e->planes[0].pos.y = 0;
	e->planes[0].pos.z = 0;
	e->planes[0].normale.x = 0;
	e->planes[0].normale.y = -1;
	e->planes[0].normale.z = 0;
	e->planes[0].color = 0x00ff0000;

/*	//plane 2
	ft_bzero(&e->planes[1], sizeof(t_plane));
	e->planes[1].pos.x = -5;
	e->planes[1].pos.y = 0;
	e->planes[1].pos.z = 0;
	e->planes[1].normale.x = 1;
	e->planes[1].normale.y = 0;
	e->planes[1].normale.z = 0;
	e->planes[1].color = 0x000000ff;
*/	
	//sphere 1
	ft_bzero(&e->spheres[0], sizeof(t_sphere));
	e->spheres[0].pos.x = 0;
	e->spheres[0].pos.y = -5;
	e->spheres[0].pos.z = 0;
	e->spheres[0].dir.x = 0;
	e->spheres[0].dir.y = 0;
	e->spheres[0].dir.z = 0;
	e->spheres[0].radius = 2;
	e->spheres[0].color = 0x0000ff00;

	//sphere 2
	ft_bzero(&e->spheres[1], sizeof(t_sphere));
	e->spheres[1].pos.x = 0;
	e->spheres[1].pos.y = -5;
	e->spheres[1].pos.z = 10;
	e->spheres[1].dir.x = 0;
	e->spheres[1].dir.y = 0;
	e->spheres[1].dir.z = 0;
	e->spheres[1].radius = 3;
	e->spheres[1].color = 0x00660066;

	//lights
	ft_bzero(&e->lights[0], sizeof(t_light));
	e->lights[0].pos.x = 12;
	e->lights[0].pos.y = -5;
	e->lights[0].pos.z = 10;
	e->lights[0].dir.x = 0;
	e->lights[0].dir.y = 0;
	e->lights[0].dir.z = 0;
	e->lights[0].color = 0x0000ff00;

	//lights 2
	ft_bzero(&e->lights[1], sizeof(t_light));
	e->lights[1].pos.x = -10;
	e->lights[1].pos.y = -5;
	e->lights[1].pos.z = 0;
	e->lights[1].dir.x = 0;
	e->lights[1].dir.y = 0;
	e->lights[1].dir.z = 0;
	e->lights[1].color = 0x00ffffff;


	//cone 1
	ft_bzero(&e->cones[0], sizeof(t_cone));
	e->cones[0].pos.x = 25;
	e->cones[0].pos.y = 0;
	e->cones[0].pos.z = 10;
	e->cones[0].dir.x = 0;
	e->cones[0].dir.y = 0;
	e->cones[0].dir.z = 0;
	e->cones[0].angle = 2;
	e->cones[0].color = 0x0000ff33;	

	//cylinder 1
	ft_bzero(&e->cylinders[0], sizeof(t_cylinder));
	e->cylinders[0].pos.x = -20;
	e->cylinders[0].pos.y = 0;
	e->cylinders[0].pos.z = 10;
	e->cylinders[0].dir.x = 0;
	e->cylinders[0].dir.y = 0;
	e->cylinders[0].dir.z = 0;
	e->cylinders[0].radius = 3.0;
	e->cylinders[0].color = 0x000033ff;	

}

void		frame_init(t_env *e)
{
	int		bpp;
	int		row;
	int		endian;

	if (!(e->frame = malloc(sizeof(t_frame))))
		s_error("\x1b[2;31mCan't initialize the frame\x1b[0m", e);
	e->frame->w = e->win_w;
	e->frame->h = e->win_h;
	if (!(e->frame->ptr = mlx_new_image(e->mlx, e->frame->w, e->frame->h)))
		s_error("\x1b[2;31mCan't create new mlx image\x1b[0m", e);
	if (!(e->frame->pix = mlx_get_data_addr(e->frame->ptr, \
							&(bpp), &(row), &(endian))))
		s_error("\x1b[2;31mCan't create get image address\x1b[0m", e);
	e->frame->bpp = bpp;
	e->frame->row = row;
	e->frame->endian = endian;
	load_scene(e);
}

void		init(t_env *e)
{
	ft_bzero(e, sizeof(t_env));
	e->debug = DBUG;
	e->win_w = WIDTH;
	e->win_h = HEIGHT;
	e->cen_x = e->win_w / 2;
	e->cen_y = e->win_h / 2;
	e->mou_x = 0;
	e->mou_y = 0;
	e->gpu = IS_GPU;
	e->param.bloom = 1.80;
	e->run = 1;

	if (!(e->mlx = mlx_init()))
		s_error("\x1b[2;31mError can't initialize minilibx\x1b[0m", e);
	if (!(e->win = mlx_new_window(e->mlx, e->win_w, e->win_h, "RTv1")))
		s_error("\x1b[2;31mError minilibx window creation failed\x1b[0m", e);
	frame_init(e);
	if (opencl_init(e) != 0)
	{
		e->gpu = 0;
		opencl_init(e);
	}
	set_hooks(e);
}
