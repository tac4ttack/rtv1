#include "rtv1.h"

int			check_char(char c)
{
	if (c != '"' && c != 10 && c != ',' && c != ' ' && c != '<' && c != '>' && \
		c != '.' && c != '/' && c != '-' && c != '=' && c != '!' && c != 9 && \
		ft_isdigit(c) != 1 && ft_isalphalowercase(c) != 1)
			return (1);
	else
		return (0);
}

int			check_valid_char(t_env *e, char *buf)
{
	int		i;
	
	i = -1;
	while (buf[++i])
	{
		if (check_char(buf[i]) != 0)
			return (1);
		(buf[i] == '<' ? e->xml->lbra++ : 0);
		(buf[i] == '>' ? e->xml->rbra++ : 0);
		(buf[i] == '/' ? e->xml->slas++ : 0);
		(buf[i] == '"' ? e->xml->dquo++ : 0);
		(buf[i] == '!' ? e->xml->excl++ : 0);
	}
	return (0);
}
char		*check_comment_active(t_env *e, char *buf)
{
	int		i;

	i = 0;
	if (ft_strstr(buf, "<!--") != NULL)
		s_error("\x1b[2;31mError, nested comment\x1b[0m", e);
	while (buf[i])
	{
		if (buf[i] == '-' && buf[i + 1] == '-' && buf[i + 2] == '>')
		{	
			ft_memset(&buf[i], ' ', 3);
			e->xml->comment = 0;
			break ;
		}
		buf[i] = ' ';
		i++;
	}
	return (ft_strtrim_free(buf));
}

char		*check_comment_inactive(t_env *e, char *buf)
{
	char	*cur;
	int		i;

	i = 0;
	if ((cur = ft_strstr(buf, "<!--")) != NULL)
	{
		ft_memset(cur, ' ', 4);
		e->xml->comment = 1;
		while (cur[i])
		{
			if (cur[i] == '<' && cur[i + 1] == '!' && cur[i + 2] == '-' && cur[i + 3] == '-')
				s_error("\x1b[2;31mError, nested comment\x1b[0m", e);
			if (cur[i] == '-' && cur[i + 1] == '-' && cur[i + 2] == '>')
			{	
				ft_memset(&cur[i], ' ', 3);
				e->xml->comment = 0;
				break ;
			}
			cur[i] = ' ';
			i++;
		}
	}
	return (ft_strtrim_free(buf));
}

char		*check_buf(t_env *e, char *buf)
{
	if (e->xml->comment == 0)
		buf = check_comment_inactive(e, buf);	
 	if (e->xml->comment == 1)
		buf = check_comment_active(e, buf);
//	printf("%s\n", buf);
	if (e->xml->comment == 0)
		if (check_valid_char(e, buf) != 0)
			s_error("\x1b[2;31mError, invalid scene content\x1b[0m", e);
	return(buf);
}

int			check_xml_header(char *buf)
{
	if (ft_strcmp(buf, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>") != 0)
		return (0);
	else
		return (1);
}

void		read_file(t_env *e)
{
	int		count;
	int		status;
	char	*buf;

	count = 0;
	status = 1;
	while (status == 1)
	{
		status = get_next_line(e->xml->scene_fd, &buf);
		if (status == -1)
			p_error("\x1b[2;31mError reading scene\x1b[0m", e);
		else if (status == 0)
			break ;
		else
		{	
			if (count == 0 && check_xml_header(buf) != 1)
				s_error("\x1b[2;31mError missing scene header\x1b[0m", e);
			if (count > 0)
				buf = check_buf(e, buf);
			e->xml->scene = ft_strjoin_free(e->xml->scene, \
								ft_strtrim(ft_strjoin_frs1(buf, " ")));
			count++;
		}
	}
	close(e->xml->scene_fd);
	printf("SCENE = \n%s\n", e->xml->scene);
}

void		get_file(t_env *e, int ac, char *av)
{
	if (ac > 2)
		s_error("\x1b[2;31mError, too many arguments\x1b[0m", e);
	else if (ac == 2)
		e->xml->scene = ft_strdup(av);
	else
	{
		ft_putendl("\x1b[2;33mNo scene file specified, loading default\x1b[0m");
		e->xml->scene = ft_strdup("./default.xml");
	}
	if ((e->xml->scene_fd = open(e->xml->scene, O_RDONLY)) < 0)
		p_error("\x1b[2;31mCan't open scene file\x1b[0m", e);
	ft_bzero((void*)e->xml->scene, ft_strlen(e->xml->scene));
	e->xml->comment = 0;
	read_file(e);
}
