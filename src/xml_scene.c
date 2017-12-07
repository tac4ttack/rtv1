#include "rtv1.h"

static void xml_scene_res(t_env *e, char **att, int *i)
{
	int		w;
	int		h;

	if (e && att && i)
	{
		w = ft_atoi(att[(*i)++] + 5);
		h = ft_atoi(att[(*i)++]);
		if (w == 0 || h == 0)
			s_error("\x1b[2;31mError scene Width/Height must be > 0\x1b[0m", e);
		else
		{
			e->param.win_w = (w < 0 ? -w : w);
			e->param.win_h = (h < 0 ? -h : h);
		}
	}
	else
		s_error("\x1b[2;31mError reading RESOLUTION from scene node\x1b[0m", e);
}

static void	xml_scene_ambient(t_env *e, char **att, int *i)
{
	if (e && att && i)
	{
		if (att[(*i)] == NULL)
			s_error("\x1b[2;31mError reading AMBIENT scene node\x1b[0m", e);
		e->param.ambient.x = ft_atof(att[(*i)++] + 9);
		e->param.ambient.y = ft_atof(att[(*i)++]);
		e->param.ambient.z = ft_atof(att[(*i)++]);
// RAJOUTER CONTROLE DE LA VALEUR QUAND ON SAURA QUELLE VALEUR CA DOIT AVOIR t(ಠ益ಠt)
	}
	else
		s_error("\x1b[2;31mError reading AMBIENT from scene node\x1b[0m", e);
}

static void	xml_scene_parse(t_env *e, char *node)
{
	int		i;
	char	**tmp;

	i = 1;
	tmp = ft_strsplit(node, ' ');
	if (ft_strncmp(tmp[i], "res=\"", 5) != 0 || tmp[i] == NULL)
		s_error("\x1b[2;31mError in scene RESOLUTION expected in #0\x1b[0m", e);
	else
		xml_scene_res(e, tmp, &i);
	printf("SCENE\nwidth = %d | height = %d\n", e->param.win_w, e->param.win_h);
	if (ft_strncmp(tmp[i], "ambient=\"", 9) != 0 || tmp[(i)] == NULL)
		s_error("\x1b[2;31mError in scene, AMBIENT expected in #1\x1b[0m", e);
	else
		xml_scene_ambient(e, tmp, &i);
	printf("a.r = %f | a.g = %f | a.b = %f\n", e->param.ambient.x, e->param.ambient.y, e->param.ambient.z);
	if (tmp[i] == NULL)
	{
		if (tmp[i - 1][ft_strlen(tmp[i - 1]) - 1] != '>')
			s_error("\x1b[2;31mError SCENE node isn't closed\x1b[0m", e);
	}
	else if (tmp[i][ft_strlen(tmp[i]) - 1] != '>')
		s_error("\x1b[2;31mError CAMERA node isn't closed\x1b[0m", e);
	xml_node_clean(tmp);
}

void		xml_node_scene(t_env *e, char *node, char mod)
{
	if (mod == 0)
	{
		if (ft_strncmp(node, "scene ", 6) != 0)
			s_error("\x1b[2;31mError in XML syntax\x1b[0m", e);
		XML->in_scene = 1;
		xml_scene_parse(e, node);
	}
	else if (mod == 1)
	{
		if (ft_strlen(node) != 8)
			s_error("\x1b[2;31mError in XML syntax\x1b[0m", e);
		XML->in_scene = 0;
	}
}
