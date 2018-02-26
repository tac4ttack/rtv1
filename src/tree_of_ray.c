#include "rtv1.h"

int		tor_flush(t_env *e)
{
	if (e->tree)
	{
		free(e->tree);
		e->tree = NULL;
		return (0);
	}
	return (1);
}

t_tor	*tor_create(t_env *e)
{
	t_tor	*tree;
	int		count;
	int		i;

	i = 0;
	count = pow(2, e->scene->depth + 1) - 1;
	tree = NULL;
	if (!(tree = malloc(sizeof(t_tor) * count)))
		s_error("\x1b[2;31mCan't initialize the Tree of Ray\x1b[0m", e);
	while (i < count)
	{
		ft_bzero(&tree[i], sizeof(t_tor));
		i++;
	}
	return (tree);
}
