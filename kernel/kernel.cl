#include "kernel_header.h"

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

unsigned int			light_angle(float angle)
{
	unsigned char		r = (SCOLOR & 0x00FF0000) >> 16;
	unsigned char		g = (SCOLOR & 0x0000FF00) >> 8;
	unsigned char		b = (SCOLOR & 0x000000FF);
	float		mult =  1.40 * angle;
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

unsigned int			light(t_hit hit, t_scene scene)
{
	int					i = -1;
	float				cos_angle = 0;

	while (++i < PARAM->n_lights)
	{
		float3		lightray = LIGHT - hit.pos;
		float		lightdist = norme_vect(lightray);
		float3		lightdir = normalize_vect(lightray);
		if ((plan = inter_plan(plan_origin, plan_normale, lightray, p)) <= 0)
			plan = 1000000000;
		if ((sphere = inter_sphere(radius, lightdir, p, boule_origin)) <= 0)
			sphere = 1000000000;
		if (plan < lightdist || sphere < lightdist)
		{
		//	printf("coucou");
			return (BACKCOLOR);
		}
		if (obj == 5)
			cos_angle = dot_vect(lightray, normale) / (norme_vect(lightray) * norme_vect(normale));
		else
			cos_angle = dot_vect(lightray, plan_normale) / (norme_vect(lightray) * norme_vect(plan_normale));
		/*if (cos_angle < 0)
			return (0x00000000);*/
		float angle = acos(cos_angle) * RAD2DEG;
		//printf("%f\n", cos_angle);
		/*if (angle > 90)
			return (BACKCOLOR);*/
	}
	return (light_angle(angle));
}

t_scene			grab_data(__constant t_cam *cameras, \
						  __constant t_cone *cones, \
						  __constant t_cylinder *cylinders, \
						  __constant t_light *lights, \
						  __constant t_plane *planes, \
						  __constant t_sphere *spheres, \
						  t_param param)
{
	t_scene	result;

	result.cameras = &cameras;
	result.cones = &cones;
	result.cylinders = &cylinders;
	result.lights = &lights;
	result.planes = &planes;
	result.spheres = &spheres;
	result.param = &param;
	return (result);
}

int				get_max_obj(t_param *param)
{
	int			res = n_cones;
	if (param->n_cylinders > res)
		res = param->n_cylinders;
	if (param->n_planes > res)
		res = param->n_planes;
	if (param->n_spheres > res)
		res = param->n_spheres;
	return (res);
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
	hit.pos = {.x = 0, .y = 0, .z = 0};
	hit.normale = {.x = 0, .y = 0, .z = 0};
	while (++i < max)
	{
		/*if (i < PARAM.n_cones)
			;
		if (i < PARAM.n_cylinders)
			;*/
		if (i < PARAM.n_planes)
			if ((dist = inter_plan(PLANE[i], ray, origin)) < hit.dist || hit.dist == 0)
			{
				hit.dist = dist;
				hit.type = 4;
				hit.id = i;
			}
		if (i < PARAM.n_spheres)
			if ((dist = inter_sphere(SPHERE[i], ray, origin)) < hit.dist || hit.dist == 0)
			{
				hit.dist = dist;
				hit.type = 4;
				hit.id = i;
			}
	}
	return (hit);
}

float3			get_hit_normale(t_scene scene, t_hit hit)
{
	float3		res;

	/*if (hit.type == 1) CONES
		;
	if (hit.type == 2) CYLINDRES
		;*/
	if (hit.type == 4)
		res = PLANE[hit.id]->normale;
	else if (hit.type == 5)
		res = hit.pos - SPHERE[hit.id]->pos;
	return (res);
}

unsigned int	get_pixel_color(t_scene scene)
{
	t_hit		hit = ray_hit(ACTIVECAM.pos, ACTIVECAM.ray, scene);

	hit.pos = mult_fvect(hit.dist, ACTIVECAM.ray) + ACTIVECAM.pos;
	hit.normale = get_hit_normale(scene, hit);
	
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

	if ((plan = inter_plan(plan_origin, plan_normale, ray, cam_origin)) < 0)
		plan = 1000000000;
	if ((sphere = inter_sphere(radius, ray, cam_origin, boule_origin)) < 0)
		sphere = 1000000000;
	if ((light = inter_sphere(radiusl, ray, cam_origin, light_origin)) < 0)
		light = 1000000000;
	if (sphere == 1000000000 && plan == 1000000000)
		OUTPUTE = BACKCOLOR;
	else if (sphere < plan && sphere < light)
		OUTPUTE = light_sphere(5, (mult_fvect(sphere, ray) + cam_origin), boule_origin, radius, light_origin, plan_origin, plan_normale);
//OUTPUTE = SCOLOR;
	else if (light < sphere && light < plan)
		OUTPUTE = LCOLOR;
	else
		OUTPUTE = light_sphere(0, (mult_fvect(plan, ray) + cam_origin), boule_origin, radius, light_origin, plan_origin, plan_normale);

