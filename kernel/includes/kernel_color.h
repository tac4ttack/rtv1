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

float3			get_obj_diffuse(t_scene scene, t_hit hit)
{
	float3	diffuse = 0;
	
	if (hit.type == 1)
		diffuse = CONES[hit.id].diff;
	if (hit.type == 2)
		diffuse = CYLIND[hit.id].diff;
	if (hit.type == 4)
		diffuse = PLANE[hit.id].diff;
	if (hit.type == 5)
		diffuse = SPHERE[hit.id].diff;
	return (diffuse);
}

unsigned int			color_diffuse(t_hit hit, t_scene scene, unsigned int color, float coef)
{
	float3			diffuse = get_obj_diffuse(scene, hit);
	unsigned int	col_r = (color & 0x00FF0000) >> 16;
	unsigned int	col_g = (color & 0x0000FF00) >> 8;
	unsigned int	col_b = (color & 0x000000FF);
	unsigned int	obj_r = (get_obj_hue(scene, hit) & 0x00FF0000) >> 16;
	unsigned int	obj_g = (get_obj_hue(scene, hit) & 0x0000FF00) >> 8;
	unsigned int	obj_b = (get_obj_hue(scene, hit) & 0x000000FF);

	col_r += obj_r * coef * diffuse.x;
	col_g += obj_g * coef * diffuse.y;
	col_b += obj_b * coef * diffuse.z;
	(col_r > 255 ? col_r = 255 : 0);
	(col_g > 255 ? col_g = 255 : 0);
	(col_b > 255 ? col_b = 255 : 0);
	return ((col_r << 16) + (col_g << 8) + col_b);
}

float3			get_obj_speculos(t_scene scene, t_hit hit)
{
	float3	speculos = 0;
	
	if (hit.type == 1)
		speculos = CONES[hit.id].spec;
	if (hit.type == 2)
		speculos = CYLIND[hit.id].spec;
	if (hit.type == 4)
		speculos = PLANE[hit.id].spec;
	if (hit.type == 5)
		speculos = SPHERE[hit.id].spec;
	return (speculos);
}

/*unsigned int			color_specular(t_hit hit, t_scene scene, unsigned int color, float coef)
{
	float3			speculos = get_obj_speculos(scene, hit);
	float			old_coef = coef;
	unsigned int	col_r = (color & 0x00FF0000) >> 16;
	unsigned int	col_g = (color & 0x0000FF00) >> 8;
	unsigned int	col_b = (color & 0x000000FF);

//	coef = pow(coef, 2) * 0.9;
//	printf("%f\n", coef);
	coef = 255 * pow(old_coef, LIGHT[hit.id].intensity) * speculos.x;
	col_r += coef;
	coef = 255 * pow(old_coef, LIGHT[hit.id].intensity) * speculos.y;
	col_g += coef;
	coef = 255 * pow(old_coef, LIGHT[hit.id].intensity) * speculos.z;
	col_b += coef;
	(col_r > 255 ? col_r = 255 : 0);
	(col_g > 255 ? col_g = 255 : 0);
	(col_b > 255 ? col_b = 255 : 0);
	return ((col_r << 16) + (col_g << 8) + col_b);
}
*/


unsigned int			color_specular(t_hit hit, t_scene scene, unsigned int color, float coef)
{
	float3			speculos = get_obj_speculos(scene, hit);
	float			old_coef = coef;
	unsigned int	col_r = (color & 0x00FF0000) >> 16;
	unsigned int	col_g = (color & 0x0000FF00) >> 8;
	unsigned int	col_b = (color & 0x000000FF);
	unsigned int	obj_r = (get_obj_hue(scene, hit) & 0x00FF0000) >> 16;
	unsigned int	obj_g = (get_obj_hue(scene, hit) & 0x0000FF00) >> 8;
	unsigned int	obj_b = (get_obj_hue(scene, hit) & 0x000000FF);

//	coef = pow(coef, 2) * 0.9;
//	printf("%f\n", coef);
	col_r += (obj_r / 0xff) * pow(coef, LIGHT[hit.id].intensity) * speculos.x;
	col_g += (obj_g / 0xff) * pow(coef, LIGHT[hit.id].intensity) * speculos.y;
	col_b += (obj_b / 0xff) * pow(coef, LIGHT[hit.id].intensity) * speculos.z;
	(col_r > 255 ? col_r = 255 : 0);
	(col_g > 255 ? col_g = 255 : 0);
	(col_b > 255 ? col_b = 255 : 0);
	return ((col_r << 16) + (col_g << 8) + col_b);
}
