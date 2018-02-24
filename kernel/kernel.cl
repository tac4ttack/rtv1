#include "kernel_header.hcl"
#include "kernel_matrix.hcl"
#include "kernel_cam.hcl"
#include "kernel_color.hcl"
#include "kernel_cone.hcl"
#include "kernel_cylinder.hcl"
#include "kernel_data.hcl"
#include "kernel_debug.hcl"
#include "kernel_plane.hcl"
#include "kernel_sphere.hcl"

static t_hit			ray_hit(const __local t_scene *scene, const float3 origin, const float3 ray)
{
	unsigned int			i = 0;
	int						max = get_max_obj(scene);
	t_hit					hit = hit_init();
	float					dist = 0;

	while (i < max)
	{
		if (i < scene->n_cones)
			if (((dist = inter_cone(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 1;
				hit.id = i;
			}
		if (i < scene->n_cylinders)
			if (((dist = inter_cylinder(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 2;
				hit.id = i;
			}
		if (i < scene->n_planes)
			if (((dist = inter_plan(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 4;
				hit.id = i;
			}
		if (i < scene->n_spheres)
			if (((dist = inter_sphere(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 5;
				hit.id = i;
			}
		i++;
	}
	return (hit);
}

static t_hit			ray_hit2(const __local t_scene *scene, const float3 origin, const float3 ray)
{
	unsigned int			i = 0;
	int						max = get_max_obj(scene);
	t_hit					hit = hit_init();
	float					dist = 0;

	while (i < max)
	{
		if (i < scene->n_cones)
			if (((dist = inter_cone(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 1;
				hit.id = i;
			}
		if (i < scene->n_cylinders)
			if (((dist = inter_cylinder(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 2;
				hit.id = i;
			}
		if (i < scene->n_planes)
			if (((dist = inter_plan(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 4;
				hit.id = i;
			}
		if (i < scene->n_spheres)
			if (((dist = inter_sphere(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 5;
				hit.id = i;
			}
		i++;
	}
	return (hit);
}

float3			get_hit_normale(const __local t_scene *scene, float3 ray, t_hit hit)
{
	float3		res, save;

	if (hit.type == 1)
		res = get_cone_normale(scene, hit);
	else if (hit.type == 2)
		res = get_cylinder_normal(scene, hit);
	else if (hit.type == 4)
	{
		if (dot(PLANE[hit.id].normale, -ray) < 0)
			res = -PLANE[hit.id].normale;
		else
			res = PLANE[hit.id].normale;

		if (scene->flag & OPTION_WAVE)
		{
			/*					VAGUELETTE						*/
			save = res;
			save.y = res.y + 0.8 * sin((hit.pos.x + scene->u_time));
			return (fast_normalize(save));
		}
	}
	else if (hit.type == 5)
		res = hit.pos - SPHERE[hit.id].pos;
	save = res;
	if (scene->flag & OPTION_WAVE)
	{
		/*						VAGUELETTE							*/
		save.x = res.x + 0.8 * sin(res.y * 10 + scene->u_time);
		//save.z = save.z + 0.8 * sin(save.x * 10 + scene->u_time);
		//save.y = res.y + 0.8 * sin(res.x * 10 + scene->u_time);
	}

	return (fast_normalize(save));
}

unsigned int			color_diffuse2(const __local t_scene *scene, const t_hit hit, \
										const t_hit light_hit, const unsigned int color, const float coef)
{
	float3		__private	diffuse = get_obj_diffuse(scene, hit);
	float		__private	brightness = (float __private)LIGHT[light_hit.id].brightness;

	if (hit.type == 1)
		diffuse = (float3 __private)CONES[hit.id].diff;
	else if (hit.type == 2)
		diffuse = (float3 __private)CYLIND[hit.id].diff;
	else if (hit.type == 4)
		diffuse = (float3 __private)PLANE[hit.id].diff;
	else if (hit.type == 5)
		diffuse = (float3 __private)SPHERE[hit.id].diff;
	else
		diffuse = 0.f;

	int __private hue;

	if (hit.type == 1)
		hue = (int __private)CONES[hit.id].color;
	if (hit.type == 2)
		hue = (int __private)CYLIND[hit.id].color;
	if (hit.type == 3)
		hue = (int __private)LIGHT[hit.id].color;
	if (hit.type == 4)
		hue = (int __private)PLANE[hit.id].color;
	if (hit.type == 5)
		hue = (int __private)SPHERE[hit.id].color;
	int __private hue_light;

	if (hit.type == 1)
		hue_light = (int __private)CONES[light_hit.id].color;
	if (hit.type == 2)
		hue_light = (int __private)CYLIND[light_hit.id].color;
	if (hit.type == 3)
		hue_light = (int __private)LIGHT[light_hit.id].color;
	if (hit.type == 4)
		hue_light = (int __private)PLANE[light_hit.id].color;
	if (hit.type == 5)
		hue_light = (int __private)SPHERE[light_hit.id].color;
	unsigned int	col_r = (color & 0xFF0000) >> 16;
	unsigned int	col_g = (color & 0x00FF00) >> 8;
	unsigned int	col_b = (color & 0x0000FF);
	unsigned int	obj_r = (hue & 0xFF0000) >> 16;
	unsigned int	obj_g = (hue & 0x00FF00) >> 8;
	unsigned int	obj_b = (hue & 0x00000FF);
	unsigned int	l_r = (hue_light & 0xFF0000) >> 16;
	unsigned int	l_g = (hue_light & 0x00FF00) >> 8;
	unsigned int	l_b = (hue_light & 0x0000FF);

	col_r += ((l_r * brightness) + obj_r) * coef * diffuse.x;
	col_g += ((l_g * brightness) + obj_g) * coef * diffuse.y;
	col_b += ((l_b * brightness) + obj_b) * coef * diffuse.z;
	(col_r > 255 ? col_r = 255 : 0);
	(col_g > 255 ? col_g = 255 : 0);
	(col_b > 255 ? col_b = 255 : 0);
	return ((col_r << 16) + (col_g << 8) + col_b);
}

unsigned int			color_specular2(const __local t_scene *scene, const t_hit hit, \
										const t_hit light_hit, const unsigned int color, const float coef)
{
	float3 __private	speculos = 0.f;
	if (hit.type == 1)
		speculos = (float3 __private)CONES[hit.id].spec;
	else if (hit.type == 2)
		speculos = (float3 __private)CYLIND[hit.id].spec;
	else if (hit.type == 4)
		speculos = (float3 __private)PLANE[hit.id].spec;
	else if (hit.type == 5)
		speculos = (float3 __private)SPHERE[hit.id].spec;
	else
		speculos = 0.f;
	float			old_coef = coef;
	unsigned int	col_r = (color & 0x00FF0000) >> 16;
	unsigned int	col_g = (color & 0x0000FF00) >> 8;
	unsigned int	col_b = (color & 0x000000FF);

	float pow_of_spec;
	pow_of_spec = native_powr(old_coef, (int)(LIGHT[light_hit.id].shrink));
 	int light_color = LIGHT[light_hit.id].color;
	//printf("%.2f\n", pow_of_spec);
	//float a = pow_of_spec * 2;
	col_r += (((light_color & 0xFF0000) >> 16) * pow_of_spec) * speculos.x;
	//printf("%.2f\n", speculos.x);
	col_g += ((light_color & 0x00FF00) >> 8) * pow_of_spec * speculos.y;
	col_b += (light_color & 0x0000FF) * pow_of_spec * speculos.z;
	(col_r > 255 ? col_r = 255 : 0);
	(col_g > 255 ? col_g = 255 : 0);
	(col_b > 255 ? col_b = 255 : 0);
	return ((col_r << 16) + (col_g << 8) + col_b);
}

unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	int					i = -1;
//	unsigned int		res_color = get_ambient(scene, get_obj_hue(scene, hit));
float				tmp2;
	float				tmp;
	float3				reflect = 0;
	unsigned int __private obj_color;
	if (hit.type == 1)
		obj_color = (unsigned int __private)CONES[hit.id].color;
	if (hit.type == 2)
		obj_color = (unsigned int __private)CYLIND[hit.id].color;
	if (hit.type == 3)
		obj_color = (unsigned int __private)LIGHT[hit.id].color;
	if (hit.type == 4)
		obj_color = (unsigned int __private)PLANE[hit.id].color;
	if (hit.type == 5)
		obj_color = (unsigned int __private)SPHERE[hit.id].color;
	unsigned int r, g, b;

	r = (obj_color & 0xFF0000) >> 16;
	g = (obj_color & 0x00FF00) >> 8;
	b = (obj_color & 0x0000FF);
	r = (0.01 + r * scene->ambient.x > 255 ? 255 : 0.01 + r * scene->ambient.x);
	g = (0.01 + g * scene->ambient.y > 255 ? 255 : 0.01 + g * scene->ambient.y);
	b = (0.01 + b * scene->ambient.z > 255 ? 255 : 0.01 + b * scene->ambient.z);
	unsigned int res_color = ((r << 16) + (g << 8) + b);

//	unsigned int res_color = 0x0FF0FF;
	t_light_ray			light_ray;
	t_hit				light_hit;// = hit_init();
	light_hit.dist = 0.0;
	light_hit.type = 0;
	light_hit.id = 0;
	light_hit.pos = 0.0;
	light_hit.normale = 0.0;

	while (++i < scene->n_lights)
	{
		tmp = 0;
		tmp2 = 0;
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist  && light_hit.dist > 0)
		{
			;
		}
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0.005)
			{
				float3		__private	diffuse = get_obj_diffuse(scene, hit);
				float		__private	brightness = (float __private)LIGHT[light_hit.id].brightness;

				if (hit.type == 1)
					diffuse = (float3 __private)CONES[hit.id].diff;
				else if (hit.type == 2)
					diffuse = (float3 __private)CYLIND[hit.id].diff;
				else if (hit.type == 4)
					diffuse = (float3 __private)PLANE[hit.id].diff;
				else if (hit.type == 5)
					diffuse = (float3 __private)SPHERE[hit.id].diff;
				else
					diffuse = 0.f;

				int __private hue;

				if (hit.type == 1)
					hue = (int __private)CONES[hit.id].color;
				if (hit.type == 2)
					hue = (int __private)CYLIND[hit.id].color;
				if (hit.type == 3)
					hue = (int __private)LIGHT[hit.id].color;
				if (hit.type == 4)
					hue = (int __private)PLANE[hit.id].color;
				if (hit.type == 5)
					hue = (int __private)SPHERE[hit.id].color;
				int __private hue_light;

				if (hit.type == 1)
					hue_light = (int __private)CONES[light_hit.id].color;
				if (hit.type == 2)
					hue_light = (int __private)CYLIND[light_hit.id].color;
				if (hit.type == 3)
					hue_light = (int __private)LIGHT[light_hit.id].color;
				if (hit.type == 4)
					hue_light = (int __private)PLANE[light_hit.id].color;
				if (hit.type == 5)
					hue_light = (int __private)SPHERE[light_hit.id].color;
				unsigned int	col_r = (res_color & 0xFF0000) >> 16;
				unsigned int	col_g = (res_color & 0x00FF00) >> 8;
				unsigned int	col_b = (res_color & 0x0000FF);
				unsigned int	obj_r = (hue & 0xFF0000) >> 16;
				unsigned int	obj_g = (hue & 0x00FF00) >> 8;
				unsigned int	obj_b = (hue & 0x00000FF);
				unsigned int	l_r = (hue_light & 0xFF0000) >> 16;
				unsigned int	l_g = (hue_light & 0x00FF00) >> 8;
				unsigned int	l_b = (hue_light & 0x0000FF);

				col_r += ((l_r * brightness) + obj_r) * tmp * diffuse.x;
				col_g += ((l_g * brightness) + obj_g) * tmp * diffuse.y;
				col_b += ((l_b * brightness) + obj_b) * tmp * diffuse.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
			reflect = fast_normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp2 = dot(reflect, -ray);
			if (tmp2 > 0.005)
			{
				//res_color = color_specular2(scene, hit, light_hit, res_color, tmp2);
			}
		}
	}
	return (res_color);
}

unsigned int			phong2(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	int					i;
	i = 0;
	unsigned int		res_color;
	res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	tmp = 0;
	float3				reflect;
	reflect = 0;
	float3 __private	diffuse;
	diffuse = 0;
	float __private	brightness;
	brightness = 0;
	int __private hue;
	hue = 0;
	int __private hue_light;
	hue_light = 0;
	unsigned int __private col_r, col_g, col_b, obj_r, obj_g, obj_b, l_r, l_b, l_g;
	col_r = 0;
	col_g = 0;
	col_b = 0;
	obj_r = 0;
	obj_g = 0;
	obj_b = 0;
	l_r = 0;
	l_g = 0;
	l_b = 0;
	t_light_ray			light_ray;
	t_hit				light_hit;
	float __private pow_of_spec;
	pow_of_spec = 0;
	int __private light_color;
	light_color = 0;
	float3 __private speculos;
	speculos = 0;

	light_ray.dir = LIGHT[0].pos - hit.pos;
	light_ray.dist = fast_length(light_ray.dir);
	light_ray.dir = fast_normalize(light_ray.dir);
	light_hit = ray_hit(scene, hit.pos, light_ray.dir);
	light_hit.id = i;
	light_hit.type = 3;

		tmp = 0;
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
			res_color = 0;
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0.f)
			{
				brightness = (float __private)LIGHT[light_hit.id].brightness;

				if (hit.type == 1)
					diffuse = (float3 __private)CONES[hit.id].diff;
				else if (hit.type == 2)
					diffuse = (float3 __private)CYLIND[hit.id].diff;
				else if (hit.type == 4)
					diffuse = (float3 __private)PLANE[hit.id].diff;
				else if (hit.type == 5)
					diffuse = (float3 __private)SPHERE[hit.id].diff;
				else
					diffuse = 0.f;


				if (hit.type == 1)
					hue = (int __private)CONES[hit.id].color;
				if (hit.type == 2)
					hue = (int __private)CYLIND[hit.id].color;
				if (hit.type == 3)
					hue = (int __private)LIGHT[hit.id].color;
				if (hit.type == 4)
					hue = (int __private)PLANE[hit.id].color;
				if (hit.type == 5)
					hue = (int __private)SPHERE[hit.id].color;

				if (hit.type == 1)
					hue_light = (int __private)CONES[light_hit.id].color;
				if (hit.type == 2)
					hue_light = (int __private)CYLIND[light_hit.id].color;
				if (hit.type == 3)
					hue_light = (int __private)LIGHT[light_hit.id].color;
				if (hit.type == 4)
					hue_light = (int __private)PLANE[light_hit.id].color;
				if (hit.type == 5)
					hue_light = (int __private)SPHERE[light_hit.id].color;
				col_r = (res_color & 0xFF0000) >> 16;
				col_g = (res_color & 0x00FF00) >> 8;
				col_b = (res_color & 0x0000FF);
				obj_r = (hue & 0xFF0000) >> 16;
				obj_g = (hue & 0x00FF00) >> 8;
				obj_b = (hue & 0x00000FF);
				l_r = (hue_light & 0xFF0000) >> 16;
				l_g = (hue_light & 0x00FF00) >> 8;
				l_b = (hue_light & 0x0000FF);

				col_r += ((l_r * brightness) + obj_r) * tmp * diffuse.x;
				col_g += ((l_g * brightness) + obj_g) * tmp * diffuse.y;
				col_b += ((l_b * brightness) + obj_b) * tmp * diffuse.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
		//		res_color = color_diffuse(scene, hit, light_hit, res_color, tmp);
			reflect = fast_normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > 0.f)
			{
				speculos = 0.f;
				if (hit.type == 1)
					speculos = (float3 __private)CONES[hit.id].spec;
				else if (hit.type == 2)
					speculos = (float3 __private)CYLIND[hit.id].spec;
				else if (hit.type == 4)
					speculos = (float3 __private)PLANE[hit.id].spec;
				else if (hit.type == 5)
					speculos = (float3 __private)SPHERE[hit.id].spec;
				else
					speculos = 0.f;
				col_r = (res_color & 0x00FF0000) >> 16;
				col_g = (res_color & 0x0000FF00) >> 8;
				col_b = (res_color & 0x000000FF);

				pow_of_spec = native_powr(tmp, (LIGHT[light_hit.id].shrink));
				light_color = LIGHT[light_hit.id].color;
				col_r += (((light_color & 0xFF0000) >> 16) * pow_of_spec) * speculos.x;
				col_g += ((light_color & 0x00FF00) >> 8) * pow_of_spec * speculos.y;
				col_b += (light_color & 0x0000FF) * pow_of_spec * speculos.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);
				/*col_r += ((LIGHT[light_hit.id].color & 0x00FF0000) >> 16) * pow_of_spec * speculos.x;
				col_g += ((LIGHT[light_hit.id].color & 0x0000FF00) >> 8) * pow_of_spec * speculos.y;
				col_b += (LIGHT[light_hit.id].color & 0x000000FF) * pow_of_spec * speculos.z;
				(col_r > 255 ? col_r = 255 : 0);
				(col_g > 255 ? col_g = 255 : 0);
				(col_b > 255 ? col_b = 255 : 0);*/
				res_color = ((col_r << 16) + (col_g << 8) + col_b);
			}
		}
	return (res_color);
}

unsigned int			phong3(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	int					i = -1;
	unsigned int		res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	float3				reflect = 0;

	t_light_ray			light_ray;
	t_hit				light_hit = hit_init();

	while (++i < scene->n_lights)
	{
		tmp = 0;
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		{
		}
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0)
				res_color = color_diffuse(scene, hit, light_hit, res_color, tmp);
			reflect = fast_normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > 0)
				res_color = color_specular(scene, hit, light_hit, res_color, tmp);
		}
	}
	return (res_color);
}

unsigned int			phong4(const __local t_scene *scene, const t_hit hit, const float3 ray)
{
	int					i = -1;
	unsigned int		res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	float3				reflect = 0;

	t_light_ray			light_ray;
	t_hit				light_hit = hit_init();

	while (++i < scene->n_lights)
	{
		tmp = 0;
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		{
		}
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0)
				res_color = color_diffuse(scene, hit, light_hit, res_color, tmp);
			reflect = fast_normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp = dot(reflect, -ray);
			if (tmp > 0)
				res_color = color_specular(scene, hit, light_hit, res_color, tmp);
		}
	}
	return (res_color);
}

static unsigned int		bounce(const __local t_scene *scene, const float3 ray, const t_hit old_hit, const int depth)
{
	int				i = depth;
	unsigned int	color = 0;
	float3			reflex = 0;
	t_hit			new_hit;
	while (i > 0)
	{
		reflex = fast_normalize(ray - (2 * (float)dot(old_hit.normale, ray) * old_hit.normale));
		new_hit.dist = MAX_DIST;
		new_hit = ray_hit(scene, old_hit.pos, reflex);
		if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
		{
			new_hit.pos = (new_hit.dist * reflex) + old_hit.pos;
			new_hit.normale = get_hit_normale(scene, ray, new_hit);
			new_hit.pos = new_hit.pos + ((new_hit.dist / 100) * new_hit.normale);
			color += 0.1 * phong2(scene, new_hit, reflex);
		}
		i--;
	}
	return (color);
}

static unsigned int	get_pixel_color(const __local t_scene *scene, float3 ray)
{
	t_hit			hit;
	int				depth = scene->depth;
	unsigned int	color  = 0;
	unsigned int	bounce_color = 0;

	hit.dist = MAX_DIST;
	hit = ray_hit(scene, (ACTIVECAM.pos), ray);
	if (hit.dist > 0 && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos);
		hit.normale = get_hit_normale(scene, ray, hit);
		hit.pos = hit.pos + ((hit.dist / 100) * hit.normale);
		color = phong2(scene, hit, ray);
		if (depth > 0)
			bounce_color = bounce(scene, ray, hit, depth);
		return (color + bounce_color);
//		return (blend_add(color, 0.8*bounce_color));
	}
	return (get_ambient(scene, BACKCOLOR));
}

__kernel void	ray_trace(	__global	char		*output,
							__global	t_hit		*target_obj,
							__global	t_scene		*scene_data,
							__global	t_cam		*cameras_data,
							__global	t_cone		*cones_data,
							__global	t_cylinder	*cylinders_data,
							__global	t_light		*lights_data,
							__global	t_plane		*planes_data,
							__global	t_sphere	*spheres_data,
							__local		t_scene		*scene,
							__local		t_cam		*cameras,
							__local		t_cone		*cones,
							__local		t_cylinder	*cylinders,
							__local		t_light		*lights,
							__local		t_plane		*planes,
							__local		t_sphere	*spheres,
							__private	float		u_time,
							__private	int			flag)
{
 	event_t	ev;
	ev = async_work_group_copy((__local char *)scene, (__global char *)scene_data, sizeof(t_scene), 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cameras, (__global char *)cameras_data, sizeof(t_cam) * scene->n_cams, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cones, (__global char *)cones_data, sizeof(t_cone) * scene->n_cones, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)cylinders, (__global char *)cylinders_data, sizeof(t_cylinder) * scene->n_cylinders, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)lights, (__global char *)lights_data, sizeof(t_light) * scene->n_lights, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)planes, (__global char *)planes_data, sizeof(t_plane) * scene->n_planes, 0);
	wait_group_events(1, &ev);
	ev = async_work_group_copy((__local char *)spheres, (__global char *)spheres_data, sizeof(t_sphere) * scene->n_spheres, 0);
	wait_group_events(1, &ev);

	uint2	pix;
	pix.x = get_global_id(0);
	pix.y = get_global_id(1);


	scene->cameras = cameras;
	if (!pix.x && !pix.y)
	{
		printf("%i\n", sizeof(__private int));
		printf("%.2f, %.2f, %.2f\n", scene->cameras->pos.x,
		 							scene->cameras->pos.y,
									 scene->cameras->pos.z);
	}
	scene->cones = cones;
	scene->cylinders = cylinders;
	scene->lights = lights;
	scene->planes = planes;
	scene->spheres = spheres;
	scene->u_time = u_time;
	scene->flag = flag;
	if (!pix.x && !pix.y)
	{
		printf("%i\n", sizeof(__private int));
		printf("%.2f, %.2f, %.2f\n", scene->cameras->pos.x,
									scene->cameras->pos.y,
									 scene->cameras->pos.z);
	}

	int			id = pix.x + (scene->win_w * pix.y); // NE PAS VIRER ID CAR BESOIN DANS MACRO OUTPUTE

	float3	prim_ray = get_ray_cam(scene, pix);
	if (pix.x == scene->mou_x && pix.y == scene->mou_y)
		*target_obj = ray_hit(scene, ACTIVECAM.pos, prim_ray);
	OUTPUTE = get_pixel_color(scene, prim_ray);
}
