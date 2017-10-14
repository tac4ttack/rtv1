/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 16:13:01 by fmessina          #+#    #+#             */
/*   Updated: 2017/07/24 21:46:44 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_flush(char **array)
{
	int		i;

	i = 0;
	if (array == NULL)
		fdf_error("Error critical failure -> can't flush NULL array");
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int		fdf_count_rows(char **line)
{
	int	rows;

	rows = 0;
	while (line[rows])
	{
		free(line[rows]);
		rows++;
	}
	free(line);
	return (rows);
}

static int		fdf_get_z(t_map *map, char **tmp, int i, int j)
{
	int z;

	z = 0;
	if (*tmp[i + (j * map->r)] < 43 || *tmp[i + (j * map->r)] > 57)
		fdf_error("Error invalid map file (letters are forbidden)");
	else
		z = ft_atoi(tmp[i + (j * map->r)]);
	(z > map->zmax ? map->zmax = z : z);
	return (z);
}

static void		fdf_file2map(char *a_map, t_map *map)
{
	char	**tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tmp = ft_strsplit(a_map, 32);
	if (!(map->p_map = malloc(sizeof(t_fpoint) * (map->l * map->r))))
		fdf_error("Error creating point map -> error allocating memory");
	while (k < (map->l * map->r))
	{
		map->p_map[i + (j * map->r)].x = (i + 1);
		map->p_map[i + (j * map->r)].y = (j + 1);
		map->p_map[i + (j * map->r)].z = fdf_get_z(map, tmp, i, j);
		i++;
		k++;
		if (i == map->r)
		{
			i = 0;
			j++;
		}
	}
	fdf_flush(tmp);
}

t_map			fdf_file_read(char *av, t_map *map)
{
	char	*a_map;
	char	*buf;
	int		fd;

	a_map = ft_strnew(0);
	if ((fd = open(av, O_RDONLY)) >= 0)
	{
		while (get_next_line(fd, &buf) == 1)
		{
			if (map->r == -1)
				map->r = fdf_count_rows(ft_strsplit(buf, ' '));
			if (map->r != fdf_count_rows(ft_strsplit(buf, ' ')))
				fdf_error("Error parsing file -> wrong line length");
			a_map = ft_strjoin_free(a_map, ft_strjoin_frs1(buf, " "));
			map->l++;
		}
		fdf_file2map(a_map, map);
		free(a_map);
		close(fd);
	}
	else
		fdf_error("Error opening target file");
	return (*map);
}
