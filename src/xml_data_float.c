#include "rtv1.h"

void	xml_data_reflex(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading REFLEX value\x1b[0m", e);
		node->reflex = ft_atof(attributes[(*i)++] + 8);
		if (node->reflex < 0 || node->reflex > 1)
			s_error("\x1b[2;31mError REFLEX must be 0 <= n <= 1\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading REFLEX from scene\x1b[0m", e);
}

void	xml_data_speculos(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading SPECULAR value\x1b[0m", e);
		node->spec.x = ft_atof(attributes[(*i)++] + 6);
		node->spec.y = ft_atof(attributes[(*i)++]);
		node->spec.z = ft_atof(attributes[(*i)++]);
// RAJOUTER CONTROLE DE LA VALEUR QUAND ON SAURA QUELLE VALEUR CA DOIT AVOIR t(ಠ益ಠt)
		if (node->spec.x < 0 || node->spec.y < 0 || node->spec.z < 0)
			s_error("\x1b[2;31mError SPECULAR can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading SPECULAR from scene\x1b[0m", e);
}

void	xml_data_diffiouse(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading DIFFUSE value\x1b[0m", e);
		node->diff.x = ft_atof(attributes[(*i)++] + 6);
		node->diff.y = ft_atof(attributes[(*i)++]);
		node->diff.z = ft_atof(attributes[(*i)++]);
// RAJOUTER CONTROLE DE LA VALEUR QUAND ON SAURA QUELLE VALEUR CA DOIT AVOIR t(ಠ益ಠt)
		if (node->diff.x < 0 || node->diff.y < 0 || node->diff.z < 0)
			s_error("\x1b[2;31mError DIFFUSE can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading DIFFUSE from scene\x1b[0m", e);
}

void	xml_data_radius(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading RADIUS value\x1b[0m", e);
		node->radius = ft_atof(attributes[(*i)++] + 8);
		if (node->radius <= 0)
			s_error("\x1b[2;31mError RADIUS can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading RADIUS from scene\x1b[0m", e);
}

void	xml_data_angle(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading ANGLE value\x1b[0m", e);	
		node->angle = ft_atof(attributes[(*i)++] + 7);
		if (node->angle < 0)
			s_error("\x1b[2;31mError ANGLE can't be negative\x1b[0m", e);	
	}
	else
		s_error("\x1b[2;31mError reading ANGLE from scene\x1b[0m", e);	
}

// à garder au chaud pour plus tard
void	xml_data_height(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading HEIGHT value\x1b[0m", e);
		node->height = ft_atof(attributes[(*i)++] + 8);
		if (node->height < 0)
			s_error("\x1b[2;31mError HEIGHT can't be 0 or less\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading HEIGHT from scene\x1b[0m", e);
}

void	xml_data_intens(t_env *e, char **attributes, int *i, t_node *node)
{
	if (e && attributes && node)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[2;31mError reading INTENSITY value\x1b[0m", e);
		node->intensity = ft_atof(attributes[(*i)++] + 11);
		if (node->intensity < 0)
			s_error("\x1b[2;31mError INTENSITY can't be negative\x1b[0m", e);
	}
	else
		s_error("\x1b[2;31mError reading INTENSITY from scene\x1b[0m", e);
}
