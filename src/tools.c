#include "rtv1.h"

void	print_usage()
{
	ft_putendl("\ntoto");
}

void	flush(t_env *e)
{
	if (e->scene)
		free(e->scene);
	if (e->kernel_src)
		free(e->kernel_src);
	if (e->frame && e->frame->ptr)
		mlx_destroy_image(e->mlx, e->frame->ptr);
	if (e->frame)
		free(e->frame);
	if (e->win)
		mlx_destroy_window(e->mlx, e->win);
	if (e)
		free(e);
}

void	s_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[2;31mOh no I just crashed!\x1b[0m");
	ft_putendl(str);
	perror(NULL);
	flush(e);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	ft_putendl("\n\x1b[2;31mOh no I just crashed!\x1b[0m");
	perror(NULL);
	exit(EXIT_FAILURE);
}

int		quit(t_env *e)
{
	flush(e);
	ft_putendl("Exiting");
	exit(EXIT_SUCCESS);
	return (0);
}
