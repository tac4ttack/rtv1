#include "rtv1.h"

t_tor	*tor_create(t_env *e)
{
	t_tor	*tree;

	tree = NULL;
	if (!(tree = malloc(sizeof(t_tor) * (pow(2, e->scene->depth + 1) - 1))))
		s_error("\x1b[2;31mCan't initialize the Tree of Ray\x1b[0m", e);
	return (tree);
}
