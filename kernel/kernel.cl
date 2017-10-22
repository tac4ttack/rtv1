#include "kernel_header.h"
#include "kernel_data.h"
#include "kernel_vector.h"

float3			get_abc(float radius, float3 ray, float3 origin)
{
	float3		abc;

	abc.x = dot_vect(ray, ray);
	abc.y = 2 * dot_vect(ray, origin);
	abc.z = dot_vect(origin, origin) - (radius * radius);
	return (abc);
}

float			inter_sphere(t_sphere sphere, float3 ray, float3 origin)
{
	float3		abc;
	float		d;
	float		res1;
	float		res2;

	origin -= sphere.pos;
	abc = get_abc(sphere.radius, ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (1000000000);
	if (d == 0)
		return ((-abc[1]) / (2 * abc[0]));
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return(res1);
	return(res2);
}

float			inter_plan(t_plane plane, float3 ray, float3 origin)
{
	float		t;

	t = dot_vect(ray, plane.normale);
	t = dot_vect(sub_vect(plane.pos, origin), plane.normale) / t;
	if (t < 0.00001)
		return (1000000000);
	return (t);
}

void			get_ray_cam(t_cam cam, int x, int y)
{
	float3		h = mult_fvect(modh_vect(x), cam.hor);
	float3		v = mult_fvect(modv_vect(y), cam.ver);
	cam.ray = add_vect(cam.dir, v);
	cam.ray = add_vect(cam.ray, h);
}

unsigned int			light_angle(float angle, unsigned int robert_hue)
{
	unsigned char		r = (robert_hue & 0x00FF0000) >> 16;
	unsigned char		g = (robert_hue & 0x0000FF00) >> 8;
	unsigned char		b = (robert_hue & 0x000000FF);
	float				mult =  1.40 * angle;
	if (angle == 0)
		return (SCOLOR);
	if (mult > r)
		r = 0;
	else
		r -= mult;
	if (mult > g)
		g = 0;
	else
		g -= mult;
	if (mult > b)
		b = 0;
	else
		b -= mult;
	return ((r << 16) + (g << 8) + b);
}

unsigned int			get_obj_hue(t_scene scene, t_hit hit)
{
	unsigned int		color = 0;

//	CONES
//	if (i < PARAM.n_cones)
//	CYLINDERS
//	if (i < PARAM.n_cylinders)
	if (hit.type == 4)
		color = PLANE[hit.id].color;
	else if (hit.type == 5)
		color = SPHERE[hit.id].color;
	return (color);
}

float					light_angelamerkel(t_hit hit, t_light_ray light_ray)
{
	float				cos_angela;
	float				angela;

	cos_angela = dot_vect(light_ray.ray, hit.normale) / (norme_vect(light_ray.ray) * norme_vect(hit.normale));
	angela = acos(cos_angela) * RAD2DEG;
	return (angela);
}

t_hit			ray_hit(float3 origin, float3 ray, t_scene scene)
{
	int			i = -1;
	int			max = get_max_obj(PARAM);
	t_hit		hit;
	float		dist = 0;

	hit.dist = 0;
	hit.type = 0;
	hit.id = 0;
	hit.pos = (0, 0, 0);
	hit.normale = (0, 0, 0);
	while (++i < max)
	{
//		CONES
//		if (i < PARAM->n_cones)
//		CYLINDERS
//		if (i < PARAM->n_cylinders)

		if (i < PARAM->n_planes)
			if (((dist = inter_plan(PLANE[i], ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 4;
				hit.id = i;
			}
		if (i < PARAM->n_spheres)
			if (((dist = inter_sphere(SPHERE[i], ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 4;
				hit.id = i;
			}
	}
	return (hit);
}

unsigned int			light(t_hit hit, t_scene scene)
{
	int					i = -1;
	float				angle = 0;
	t_light_ray			light_ray;
	t_hit				light_hit;
	unsigned int		obj_color = get_obj_hue(scene, hit);
	unsigned int		res_color = BACKCOLOR;

	while (++i < PARAM->n_lights)
	{
		light_ray.ray = LIGHT[i].pos - hit.pos;
		light_ray.dist = norme_vect(light_ray.ray);
		light_hit = ray_hit(hit.pos, light_ray.ray, scene);
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
			;
		else
		{
			angle = light_angelamerkel(hit, light_ray);
			res_color = light_angle(angle, obj_color);
		}
	}
	return (res_color);
}

float3			get_hit_normale(t_scene scene, t_hit hit)
{
	float3		res;

//	CONES
//	if (hit.type == 1)
//	CYLINDERS
//	if (hit.type == 2)

	if (hit.type == 4)
		res = PLANE[hit.id].normale;
	else if (hit.type == 5)
		res = hit.pos - SPHERE[hit.id].pos;
	return (res);
}

unsigned int	get_pixel_color(t_scene scene)
{
	t_hit		hit;
	hit = ray_hit(ACTIVECAM.pos, ACTIVECAM.ray, scene);

	hit.pos = mult_fvect(hit.dist, ACTIVECAM.ray) + ACTIVECAM.pos;
	hit.normale = get_hit_normale(scene, hit);
	return (light(hit, scene));
}

__kernel void	ray_trace(__global char *output,
						  float3 mvt,
						  t_param param,
						  __constant t_cam *cameras,
						  __constant t_cone *cones,
						  __constant t_cylinder *cylinders,
						  __constant t_light *lights,
						  __constant t_plane *planes,
						  __constant t_sphere *spheres)
{
	int		id = get_global_id(0);
	int		x = id % WINX;
	int		y = id / WINX;

	t_scene scene = grab_data(cameras, cones, cylinders, lights, planes, spheres, param);

//	normalize_vect(plan_normale);

	get_ray_cam(ACTIVECAM, x ,y);
	OUTPUTE = get_pixel_color(scene);
}
