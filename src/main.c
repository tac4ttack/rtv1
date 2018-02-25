#include "rtv1.h"

int			main(int ac, char **av)
{
	t_env	*e;

	(ac > 2 ? print_usage() : 0);
	if (!(e = malloc(sizeof(t_env))))
		s_error("\x1b[2;31mCan't initialize RTv1 environment\x1b[0m", NULL);
	ft_bzero(e, sizeof(t_env));
	init(e, ac, av[1]);
	set_hooks(e);
	return (0);
}
