#include "rtv1.h"

static	void	check_char(t_env *e, char c)
{
//	printf("checking\n");
	if (c != '"' && c != 10 && c != ',' && c != ' ' && c != '<' && c != '>' && \
		c != '.' && c != '/' && c != '-' && c != '=' && c != '!' && \
		ft_isdigit(c) != 1 && ft_isalphalowercase(c) != 1)
	{
		printf("%c\n", c);
		s_error("\x1b[2;31mError, illegal character found in scene\x1b[0m", e);
	}
}

static	void	check_file(t_env *e)
{
	int			i;
//	int			lbra;
//	int			rbra;
//	int			bsla;
//	int			excl;
//	int			dquo;

	i = -1;
	while (e->scene[++i])
		check_char(e, e->scene[i]);
}

static	void	read_file(t_env *e)
{
	int			i;
	int			status;
	char		*buf;

	i = 0;
	status = 1;
	while (status == 1)
	{
		status = get_next_line(e->scene_fd, &buf);
		if (status == -1)
			s_error("\x1b[2;31mError reading scene\x1b[0m", e);
		else if (status == 0)
			break ;
		else
			e->scene = ft_strjoin_free(e->scene, \
						ft_strtrim_free(ft_strjoin_frs1(buf, "\n")));
		i++;
	}
	printf("SCENE = \n%s\n", e->scene);
}

void			get_file(t_env *e, int ac, char *av)
{
	if (ac > 2)
		s_error("\x1b[2;31mError, too many arguments\x1b[0m", e);
	else if (ac == 2)
		e->scene = ft_strdup(av);
	else
	{
		ft_putendl("\x1b[2;33mNo scene file specified, loading default\x1b[0m");
		e->scene = ft_strdup("./default.xml");
	}
	if ((e->scene_fd = open(e->scene, O_RDONLY)) < 0)
		s_error("\x1b[2;31mCan't open scene file\x1b[0m", e);
	ft_bzero((void*)e->scene, ft_strlen(e->scene));
	read_file(e);
	check_file(e);
}
