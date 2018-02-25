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
	t_node	*list;
	
	xml_allocate_cam(e);
	xml_allocate_cone(e);
	xml_allocate_cyl(e);
	xml_allocate_light(e);
	xml_allocate_plane(e);
	xml_allocate_sphere(e);
	list = XML->node_lst;
	while (list != NULL)
	{
		if (list->type == 0)
			xml_push_cam(e, list);
		if (list->type == 1)
			xml_push_cone(e, list);
		if (list->type == 2)
			xml_push_cyl(e, list);
		if (list->type == 3)
			xml_push_light(e, list);
		if (list->type == 4)
			xml_push_plane(e, list);
		if (list->type == 5)
			xml_push_sphere(e, list);
		list = list->next;
	}
	xml_list_clean(e, &XML->node_lst);
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
		s_error("\x1b[2;31mCan't create image address\x1b[0m", e);
	e->frame->bpp = bpp;
	e->frame->row = row;
	e->frame->endian = endian;
	load_scene(e);
}

void		init(t_env *e, int ac, char *av)
{
	ft_bzero(e, sizeof(t_env));
	ft_bzero(&e->target_obj, sizeof(t_hit));
	if (!(e->scene = malloc(sizeof(t_scene))))
		s_error("\x1b[2;31mCan't initialize scene buffer\x1b[0m", e);
	ft_bzero(e->scene, sizeof(t_scene));
	xml_init(e, ac, av);
	e->scene->depth = 0;
	e->win_w = e->scene->win_w;
	e->win_h = e->scene->win_h;
	e->count = e->win_h * e->win_w;
	e->debug = DBUG;
	e->cen_x = e->win_w / 2;
	e->cen_y = e->win_h / 2;
	e->gpu = IS_GPU;
	e->run = 0;
	if (!(e->mlx = mlx_init()))
		s_error("\x1b[2;31mError can't initialize minilibx\x1b[0m", e);
	if (!(e->win = mlx_new_window(e->mlx, e->win_w, e->win_h, "RTv1")))
		s_error("\x1b[2;31mError minilibx window creation failed\x1b[0m", e);
	frame_init(e);
	printf("%f, %f, %f\n", e->cameras[0].dir.x, e->cameras[0].dir.y, e->cameras[0].dir.z);
	if (opencl_init(e, e->count * 4) != 0)
	{
		e->gpu = 0;
		opencl_init(e, e->count * 4);
	}
}
