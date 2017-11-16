/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:01:40 by fmessina          #+#    #+#             */
/*   Updated: 2017/11/16 18:03:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// fonction de controle des resultat pour des tests
void		print_nodes(t_env *e, char **nodes)
{
	int	i = 0;
	while (i < e->xml->lbra)
	{
		// test en dessous fonctionne, peut servir a clean les comments
		if (i == 1)
		{
			char *test = ft_strstr(nodes[i], "cul");
			test++;
			test++;
			if (*test == nodes[i][6])
				printf("%c | %c\n", *test, nodes[i][6]);
		}
		printf("%s\n", nodes[i]);
		i++;
	}
}

char		**split_nodes(t_env *e, char *scene)
{
	char **split;
	if ((split = ft_strsplit(scene, '<')) == NULL)
		s_error("\x1b[2;31mError getting nodes\x1b[0m", e);
	return (split);
}

void		parse_nodes(t_env *e)
{
	char	**nodes;
	char	**tmp;
	int		i;

	e->xml->comment = 0;
	i = -1;
	nodes = split_nodes(e, e->xml->scene);
	while (++i < e->xml->lbra)
	{
	//	printf("node = %s\n", nodes[i]);
		tmp = ft_strsplit(nodes[i], ' ');
		if (ft_strcmp(tmp[0], "!--") == 0)
			printf("it's a comment!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "?xml") == 0)
			printf("it's a header!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "scene>") == 0)
			printf("it's a scene!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "/scene>") == 0)
			printf("it's a end of scene!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "cam") == 0)
			printf("it's a camera!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "cone") == 0)
			printf("it's a cone!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "cylinder") == 0)
			printf("it's a cylinder!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "light") == 0)
			printf("it's a light!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "plane") == 0)
			printf("it's a plane!\n\n");
		else if (e->xml->comment == 0 && ft_strcmp(tmp[0], "sphere") == 0)
			printf("it's a sphere!\n\n");
		else
			s_error("\x1b[2;31mError wrong node type\x1b[0m", e);
	}
//	free_nodes(e, nodes);
}
