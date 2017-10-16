#include "rtv1.h"

int	main(void)
{
	t_env *e;

	if (!(e = malloc(sizeof(t_env))))
		s_error("\x1b[2;31mCan't initialize RTv1 environment\x1b[0m");
	init(e);
	return (0);
}
