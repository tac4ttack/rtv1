#include "rtv1.h"

int			main(int ac, char **av)
{
	t_env	*e;

	(ac > 2 ? print_usage() : 0);
	if (!(e = malloc(sizeof(t_env))))
		s_error("\x1b[2;31mCan't initialize RTv1 environment\x1b[0m", NULL);
	get_file(e, ac, av[1]);
	if (load_file(e) != 0)
		ft_putendl("error in xml file, loading default scene");
	init(e);
	return (0);
}
