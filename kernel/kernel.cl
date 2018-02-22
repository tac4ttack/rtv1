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

float3			get_hit_normale(const __local t_scene *scene, float3 ray, t_hit hit)
{
	float3		res;

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
	}
	else if (hit.type == 5)
		res = hit.pos - SPHERE[hit.id].pos;
	return (fast_normalize(res));
}

static unsigned int			phong(const __local t_scene *scene, const t_hit hit, const float3 ray)
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
		light_ray.dist = length(light_ray.dir);
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
		if (tmp > 0)
			res_color = color_diffuse(scene, hit, light_hit, res_color, tmp);
		reflect = fast_normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
		tmp = dot(reflect, ray);
		if (tmp > 0)
			res_color = color_specular(scene, hit, light_hit, res_color, tmp);
		}
	}
	return (res_color);
}
static unsigned int			phong2(const __local t_scene *scene, const t_hit hit, const float3 ray)
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
		light_ray.dist = length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(scene, hit.pos, light_ray.dir);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		;
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
	hit = ray_hit(scene, (ACTIVECAM.pos /*+ scene->mvt*/), ray);
	if (hit.dist > 0 && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = (hit.dist * ray) + (ACTIVECAM.pos /*+ scene->mvt*/);
		hit.normale = get_hit_normale(scene, ray, hit);
		hit.pos = hit.pos + ((hit.dist / 100) * hit.normale);
		color = phong(scene, hit, ray);
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
							__local		t_sphere	*spheres)
{
 	event_t	ev;
	float3	test = 0;
	ev = async_work_group_copy((__local char *)scene, (__global char *)scene_data, sizeof(t_scene), 0);
	wait_group_events(1, &ev);

//	printf("ww = %d\n", scene->win_w);
	ev = async_work_group_copy((__local char *)cameras, (__global char *)cameras_data, sizeof(t_cam) * scene->n_cams, 0);
	wait_group_events(1, &ev);
//	test = scene->cameras[0].pos;
//	printf("cam x = %f y = %f z = %f\n", test.x, test.y, test.z);
	ev = async_work_group_copy((__local char *)cones, (__global char *)cones_data, sizeof(t_cone) * scene->n_cones, 0);
	wait_group_events(1, &ev);
//	test = scene->cones[0].pos;
//	printf("cone x = %f y = %f z = %f\n", test.x, test.y, test.z);
	ev = async_work_group_copy((__local char *)cylinders, (__global char *)cylinders_data, sizeof(t_cylinder) * scene->n_cylinders, 0);
	wait_group_events(1, &ev);
//	test = scene->cylinders[0].pos;
//	printf("cylinder x = %f y = %f z = %f\n", test.x, test.y, test.z);
	ev = async_work_group_copy((__local char *)lights, (__global char *)lights_data, sizeof(t_light) * scene->n_lights, 0);
	wait_group_events(1, &ev);
//	test = scene->lights[0].pos;
//	printf("light x = %f y = %f z = %f\n", test.x, test.y, test.z);
	ev = async_work_group_copy((__local char *)planes, (__global char *)planes_data, sizeof(t_plane) * scene->n_planes, 0);
	wait_group_events(1, &ev);
//	test = scene->planes[0].pos;
//	printf("plane x = %f y = %f z = %f\n", test.x, test.y, test.z);
	ev = async_work_group_copy((__local char *)spheres, (__global char *)spheres_data, sizeof(t_sphere) * scene->n_spheres, 0);
	wait_group_events(1, &ev);
//	test = scene->spheres[0].pos;
//	printf("sphere x = %f y = %f z = %f\n", test.x, test.y, test.z);

	scene->cameras = cameras;
	scene->cones = cones;
	scene->cylinders = cylinders;
	scene->lights = lights;
	scene->planes = planes;
	scene->spheres = spheres;

	uint2	pix;
	pix.x = get_global_id(0);
	pix.y = get_global_id(1);
	int			id = pix.x + (scene->win_w * pix.y); // NE PAS VIRER ID CAR BESOIN DANS MACRO OUTPUTE

	float3	prim_ray = get_ray_cam(scene, pix);
//	if (pix.x == 50 && pix.y == 500)
//	printf("Depth: [%i]\n", scene->depth);
	if (pix.x == scene->mou_x && pix.y == scene->mou_y)
		*target_obj = ray_hit(scene, ACTIVECAM.pos, prim_ray);
	OUTPUTE = get_pixel_color(scene, prim_ray);
}
