unsigned int	blend_multiply(unsigned int c1, unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	r = r1 * r2;
	g = g1 * g2;
	b = b1 * b2;
	return ((r << 16) + (g << 8) + b);
}

unsigned int	blend_add(unsigned int c1, unsigned int c2)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);
	unsigned int r2 = (c2 & 0x00FF0000) >> 16;
	unsigned int g2 = (c2 & 0x0000FF00) >> 8;
	unsigned int b2 = (c2 & 0x000000FF);

	if ((r = r1 + r2) > 255)
		r = 255;
	if ((g = g1 + g2) > 255)
		g = 255;
	if ((b = b1 + b2) > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

unsigned int	blend_ambiant(unsigned int c1)
{
	unsigned int r, g, b;
	unsigned int r1 = (c1 & 0x00FF0000) >> 16;
	unsigned int g1 = (c1 & 0x0000FF00) >> 8;
	unsigned int b1 = (c1 & 0x000000FF);

	r = r1 * 0.3;
	g = g1 * 0.3;
	b = b1 * 0.3;
	return ((r << 16) + (g << 8) + b);
}

unsigned int			get_obj_hue(t_scene scene, t_hit hit)
{
	unsigned int		color = 0;

	if (hit.type == 1)
		color = CONES[hit.id].color;
	if (hit.type == 2)
		color = CYLIND[hit.id].color;
	if (hit.type == 4)
		color = PLANE[hit.id].color;
	if (hit.type == 5)
		color = SPHERE[hit.id].color;
	return (color);
}

unsigned int	get_ambient(unsigned int obj_color, t_scene scene)
{
	unsigned int r, g, b;

	r = (obj_color & 0x00FF0000) >> 16;
	g = (obj_color & 0x0000FF00) >> 8;
	b = (obj_color & 0x000000FF);
	r = (r * PARAM->ambient.x > 255 ? 255 : r * PARAM->ambient.x);
	g = (g * PARAM->ambient.y > 255 ? 255 : g * PARAM->ambient.y);
	b = (b * PARAM->ambient.z > 255 ? 255 : b * PARAM->ambient.z);
	return ((r << 16) + (g << 8) + b);
}

unsigned int			color_diffuse(t_hit hit, t_scene scene, unsigned int color, float coef)
{
	unsigned int col_r = (color & 0x00FF0000) >> 16;
	unsigned int col_g = (color & 0x0000FF00) >> 8;
	unsigned int col_b = (color & 0x000000FF);
	unsigned int obj_r = (get_obj_hue(scene, hit) & 0x00FF0000) >> 16;
	unsigned int obj_g = (get_obj_hue(scene, hit) & 0x0000FF00) >> 8;
	unsigned int obj_b = (get_obj_hue(scene, hit) & 0x000000FF);

	col_r += obj_r * coef * 0.42;
	col_g += obj_g * coef * 0.42;
	col_b += obj_b * coef * 0.42;
	return ((col_r << 16) + (col_g << 8) + col_b);
}

unsigned int			color_specular(t_hit hit, t_scene scene, unsigned int color, float coef)
{
	unsigned int col_r = (color & 0x00FF0000) >> 16;
	unsigned int col_g = (color & 0x0000FF00) >> 8;
	unsigned int col_b = (color & 0x000000FF);

	coef = pow(coef, 64) * 0.2 * 0.2;
	col_r += coef;
	col_g += coef;
	col_b += coef;
	return ((col_r << 16) + (col_g << 8) + col_b);
}
