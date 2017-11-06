#include "kernel_header.h"
#include "kernel_data.h"
#include "kernel_vector.h"

float3					get_sphere_abc(float radius, float3 ray, float3 origin)
{
	float3		abc;

	abc.x = dot_vect(ray, ray);
	abc.y = 2 * dot_vect(ray, origin);
	abc.z = dot_vect(origin, origin) - (radius * radius);
	return (abc);
}

float					inter_sphere(t_sphere sphere, float3 ray, float3 origin)
{
	float3				abc;
	float				d;
	float				res1;
	float				res2;

	origin -= sphere.pos;
	abc = get_sphere_abc(sphere.radius, ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		return ((-abc[1]) / (2 * abc[0]));
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return(res1);
	return(res2);
}

float3					get_cylinder_abc(t_cylinder cylind, float3 ray, float3 origin)
{
	float3		abc;

	abc.x = (ray.x * ray.x) + (ray.y * ray.y);
	abc.y = 2 * ((origin.x * ray.x) + (origin.y * ray.y) \
			- (ray.x * cylind.pos.x) - (ray.y * cylind.pos.y));
	abc.z = (origin.x * origin.x) + (origin.y * origin.y) \
			+ (cylind.pos.x * cylind.pos.x) + (cylind.pos.y * cylind.pos.y) \
			- (cylind.radius * cylind.radius) \
			- 2 * ((origin.x * cylind.pos.x) + (origin.y * cylind.pos.y));
	return (abc);
}

float					inter_cylinder(t_cylinder cylind, float3 ray, float3 origin)
{
	float3				abc;
	float				d;
	float				res1;
	float				res2;

	origin -= cylind.pos;
	abc = get_cylinder_abc(cylind, ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		return ((-abc[1]) / (2 * abc[0]));
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return(res1);
	return(res2);
}

float3					get_cone_abc(t_cone cone, float3 ray, float3 origin)
{
	float3		abc;
	float		tan_alpha;

	tan_alpha = tan(cone.angle * DEG2RAD);
	abc.x = (ray.x * ray.x) + (ray.y * ray.y) - (ray.z * ray.z) * (tan_alpha * tan_alpha);
	abc.y = 2 * ((ray.x * origin.x) + (ray.y * origin.y) \
			- (ray.x * cone.pos.x) - (ray.y * cone.pos.y) \
			+ (ray.z * (cone.pos.z - origin.z)) * (tan_alpha * tan_alpha));
	abc.z = (origin.x * origin.x) + (origin.y * origin.y) \
			+ (cone.pos.x * cone.pos.x) + (cone.pos.y * cone.pos.y) \
			- 2 * ((origin.x * cone.pos.x) + (origin.y * cone.pos.y)) \
			- ((origin.z *origin.z) - 2 * (origin.z * cone.pos.z) \
			+ (cone.pos.z * cone.pos.z)) * (tan_alpha * tan_alpha);
	return (abc);
}

float					inter_cone(t_cone cone, float3 ray, float3 origin)
{
	float3				abc;
	float				d;
	float				res1;
	float				res2;

	origin -= cone.pos;
	abc = get_cone_abc(cone, ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		return ((-abc[1]) / (2 * abc[0]));
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return(res1);
	return(res2);
}

float					inter_plan(t_plane plane, float3 ray, float3 origin)
{
	float				t;

	t = dot_vect(ray, plane.normale);
	t = dot_vect(sub_vect(plane.pos, origin), plane.normale) / t;
	if (t < 0.0001)
		return (0);
	return (t);
}

float3					get_ray_cam(t_cam cam, int x, int y)
{
	float3				ray;
	float3				h = mult_fvect(modh_vect(x), cam.hor);
	float3				v = mult_fvect(modv_vect(y), cam.ver);

	ray = add_vect(cam.dir, v);
	ray = add_vect(ray, h);
	return (ray);
}

unsigned int			light_angle(float angle, unsigned int robert_hue, t_scene scene)
{
	unsigned char		r = (robert_hue & 0x00FF0000) >> 16;
	unsigned char		g = (robert_hue & 0x0000FF00) >> 8;
	unsigned char		b = (robert_hue & 0x000000FF);
	float				mult = scene.param->bloom * angle;

	if (angle == 0)
		return (robert_hue);
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

	if (hit.type == 1)
		color = CONES[hit.id].color;
	if (hit.type == 2)
		color = CYLIND[hit.id].color;
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
	//printf("%f\n", angela);
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
		if (i < PARAM->n_cones)
			if (((dist = inter_cone(CONES[i], ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 1;
				hit.id = i;
			}
		if (i < PARAM->n_cylinders)
			if (((dist = inter_cylinder(CYLIND[i], ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 2;
				hit.id = i;
			}
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
				hit.type = 5;
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
	unsigned int		res_color = light_angle(90, obj_color, scene);
	unsigned int		tmp_color = 0;

	while (++i < PARAM->n_lights)
	{
		//printf("%f\n", hit.pos.y);
		light_ray.ray = LIGHT[i].pos - hit.pos;
		light_ray.dist = norme_vect(light_ray.ray);
		light_hit = ray_hit(hit.pos, light_ray.ray, scene);
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
			;//printf("%f\n", light_hit.dist);
		else
		{
			angle = light_angelamerkel(hit, light_ray);
			if ((tmp_color = light_angle(angle, obj_color, scene)) != res_color)
				res_color = tmp_color;
			//res_color = obj_color;
		}
	}
	return (res_color);
}

float3			get_hit_normale(t_scene scene, t_hit hit)
{
	float3		res;


	if (hit.type == 1)
		res = hit.pos - CONES[hit.id].pos;
	else if (hit.type == 2)
		res = hit.pos - CYLIND[hit.id].pos;
	else if (hit.type == 4)
		res = PLANE[hit.id].normale;
	else
		res = hit.pos - SPHERE[hit.id].pos;
	return (res);
}

unsigned int	get_pixel_color(t_scene scene, float3 mvt)
{
	t_hit		hit;
	float		bias = 0.0001;

	hit = ray_hit((ACTIVECAM.pos + mvt), scene.ray, scene);
	if (hit.dist > 0)
	{
		hit.pos = mult_fvect(hit.dist, scene.ray) + (ACTIVECAM.pos + mvt);
		hit.normale = get_hit_normale(scene, hit);
		hit.pos = hit.pos + mult_fvect((bias + (hit.dist / 10000)), hit.normale);
		return (light(hit, scene));
	}
	return (BACKCOLOR);
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

	scene.ray = get_ray_cam(ACTIVECAM, x ,y);
	OUTPUTE = get_pixel_color(scene, mvt);
}
