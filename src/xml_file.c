/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:33:45 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/16 16:04:32 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			check_char(char c)
{
	if ((c < 32 || c > 125) && c != 0 && c != 9 && c != 10)
			return (1);
	else
		return (0);
}

char		*check_line(t_env *e, char *buf)			
{
	int		i;
	
	i = 0;
	while (buf[i])
	{
		if (check_char(buf[i]) != 0)
		{
			free(buf);
			s_error("\x1b[2;31mError target file is invalid\x1b[0m", e);
		}
		(buf[i] == '<' ? e->xml->lbra++ : 0);
		(buf[i] == '>' ? e->xml->rbra++ : 0);
		(buf[i] == '/' ? e->xml->slas++ : 0);
		(buf[i] == '"' ? e->xml->dquo++ : 0);
		(buf[i] == '!' ? e->xml->excl++ : 0);
		i++;
	}
	return (buf);
}

void		read_file(t_env *e)
{
	int		status;
	char	*buf;

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
			buf = check_line(e, ft_strtrim_free(buf));
			e->xml->scene = ft_strjoin_free(e->xml->scene, ft_strjoin_frs1(buf, " "));
		}
	}
	close(e->xml->scene_fd);
	printf("SCENE = \n%s\n\n", e->xml->scene);
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
	parse_nodes(e);
}
