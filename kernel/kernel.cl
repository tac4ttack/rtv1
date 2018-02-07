#include "kernel_header.h"
#include "kernel_matrix.h"
#include "kernel_cam.h"
#include "kernel_color.h"
#include "kernel_cone.h"
#include "kernel_cylinder.h"
#include "kernel_data.h"
#include "kernel_debug.h"
#include "kernel_plane.h"
#include "kernel_sphere.h"

float3					rotate_obj(float3 v, float pitch, float yaw, float roll)
{
	float3				res;

	res = rotat_zyx(v, pitch, yaw, roll);

	return (normalize(res));
}

static t_hit			ray_hit(const float3 origin, const float3 ray, const t_scene scene)
{
	unsigned int			i = 0;
	int						max = get_max_obj(PARAM);
	t_hit					hit = hit_init();
	float					dist = 0;

	while (i < max)
	{
		if (i < PARAM->n_cones)
			if (((dist = inter_cone(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 1;
				hit.id = i;
			}
		if (i < PARAM->n_cylinders)
			if (((dist = inter_cylinder(CYLIND[i], ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
		//	if (((dist = inter_cylinder(CYLIND[i].height, rotate_obj(CYLIND[i].dir, CYLIND[i].pitch, CYLIND[i].yaw, 0), CYLIND[i].radius, CYLIND[i].pos, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 2;
				hit.id = i;
			}
		if (i < PARAM->n_planes)
			if (((dist = inter_plan(scene, i, ray, origin)) < hit.dist || hit.dist == 0) && dist > 0)
			{
				hit.dist = dist;
				hit.type = 4;
				hit.id = i;
			}
		if (i < PARAM->n_spheres)
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

float3			rotate_matrix(float angle, float3 v)
{
	float3		res;

	res.x = v.x;
	res.y = (cos(angle) * v.y) - (sin(angle) * v.z);
	res.z = (sin(angle) * v.y) + (cos(angle) * v.z);
	return (res);
}

float16			trans_matrix(float3 dir, float angle)
{
	float16		res = 0;
	float3		rot = 0;

	rot = rotate_obj(dir, 0, angle, 0);
	res[0] = rot.x;
	res[1] = rot.y;
	res[2] = rot.z;
	rot = rotate_obj(dir, -angle, 0, 0);
	res[4] = rot.x;
	res[5] = rot.y;
	res[6] = rot.z;
	res[8] = dir.x;
	res[9] = dir.y;
	res[10] = dir.z;
	return (res);
}

float3			apply_matrix(float16 mat, float3 v)
{
	float3		res = 0;

	res.x = mat[0] * v.x + mat[4] * v.y + mat[8] * v.z;
	res.y = mat[1] * v.x + mat[5] * v.y + mat[9] * v.z;
	res.z = mat[2] * v.x + mat[6] * v.y + mat[10] * v.z;
	return (res);
}

float3			get_hit_normale(t_scene scene, t_hit hit)
{
	float3		res;

	if (hit.type == 1)
	{
		float k = CONES[hit.id].angle * DEG2RAD;
		k = tan(k);
		k = 1 + k * k;
		res = dot(-scene.ray, normalize(CONES[hit.id].dir)) * hit.dist - dot(ACTIVECAM.pos + PARAM->mvt - CONES[hit.id].pos, normalize(CONES[hit.id].dir));
		res = ((hit.pos - normalize(CONES[hit.id].pos)) - (k * normalize(CONES[hit.id].dir) * res)) * -1;
	}
	else if (hit.type == 2)
	{
		/*float3	base = CYLIND[hit.id].pos;
		res = hit.pos;

		res = rotate_matrix(45 * DEG2RAD, res);
		base.z = res.z;
		base = rotate_matrix(-45 * DEG2RAD, base);
		res = rotate_matrix(-45 * DEG2RAD, res);
		res -= base;*/
//		res = dot(-scene.ray, normalize(CYLIND[hit.id].dir) * hit.dist + \
//			dot(ACTIVECAM.pos + PARAM->mvt - CYLIND[hit.id].pos, normalize(CYLIND[hit.id].dir)));
//		res = hit.pos - CYLIND[hit.id].pos - normalize(CYLIND[hit.id].dir) * res;
	
	/*	res = normalize(hit.pos - CYLIND[hit.id].pos);
	// fonctionne pour cylindre aligné en Z
		if (dot(normalize(CYLIND[hit.id].dir), res) < 0)
		{
			res += normalize(CYLIND[hit.id].dir);
			res.z += 1;
		}
		else
		{
			res -= normalize(CYLIND[hit.id].dir);
			res.z += 1;
		}*/
		int		i = hit.id;
		float3	dir = rotate_obj(CYLIND[i].dir, CYLIND[i].pitch, CYLIND[i].yaw, 0);
		float16 ok = trans_matrix(dir, 90);
		//printf("the first\n0 : %f, 1 : %f, 2 : %f\n4 : %f, 5 : %f, 6 : %f\n8 : %f, 9 : %f, 10 : %f\n\n", ok[0], ok[1], ok[2], ok[4], ok[5], ok[6], ok[8], ok[9], ok[10]);
		res = apply_matrix(ok, hit.pos) - CYLIND[i].pos;
		res.z = 0;
		//ok = trans_matrix(dir, -90);
		//printf("the second\n0 : %f, 1 : %f, 2 : %f\n4 : %f, 5 : %f, 6 : %f\n8 : %f, 9 : %f, 10 : %f\n\n", ok[0], ok[1], ok[2], ok[4], ok[5], ok[6], ok[8], ok[9], ok[10]);
		res = apply_matrix(-ok, res);
		/*res = trans_matrix(dir, hit.pos);
		res = res - CYLIND[i].pos;
		res.z = 0;*/
		//res = trans_matrix(dir, res;
		/*
		nbase.dist = inter_cylinder(CYLIND[i].height, CYLIND[i].dir, CYLIND[i].radius, CYLIND[i].pos,  rotate_obj(scene.ray, -CYLIND[i].pitch, CYLIND[i].yaw, 0), (ACTIVECAM.pos + PARAM->mvt));
		nbase.pos = (ACTIVECAM.pos + PARAM->mvt) + normalize((rotate_obj(scene.ray, -CYLIND[i].pitch, -CYLIND[i].yaw, 0)) * nbase.dist);
		res = nbase.pos - CYLIND[i].pos;
		res.z = 0;
		res = rotate_obj(normalize(res), CYLIND[i].pitch, CYLIND[i].yaw, 0);*/
	}
	else if (hit.type == 4)
	{
		if (dot(PLANE[hit.id].normale, -scene.ray) < 0)
			res = -PLANE[hit.id].normale;
		else
			res = PLANE[hit.id].normale;
	}
	else if (hit.type == 5)
		res = hit.pos - SPHERE[hit.id].pos;
	return (normalize(res));
}

static unsigned int			phong(const t_hit hit, const t_scene scene)
{
	int					i = -1;
	unsigned int		res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	float3				reflect = 0;

	t_light_ray			light_ray;
	t_hit				light_hit = hit_init();

	while (++i < PARAM->n_lights)
	{
		tmp = 0;
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = length(light_ray.dir);
		light_ray.dir = normalize(light_ray.dir);
		light_hit = ray_hit(hit.pos, light_ray.dir, scene);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		;
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0)
				res_color = color_diffuse(scene, hit, light_hit, res_color, tmp);
			reflect = normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp = dot(reflect, -scene.ray);
			if (tmp > 0)
				res_color = color_specular(scene, hit, light_hit, res_color, tmp);
		}
	}
	return (res_color);
}

unsigned int			phong2(t_hit hit, t_scene scene)
{
	int					i = -1;
	unsigned int		res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp = 0;
	float3				reflect = 0;

	t_light_ray			light_ray;
	t_hit				light_hit;

	while (++i < PARAM->n_lights)
	{
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = length(light_ray.dir);
		light_ray.dir = normalize(light_ray.dir);
		light_hit = ray_hit(hit.pos, light_ray.dir, scene);
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		;
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0)
				res_color = color_diffuse(scene, hit, light_hit, res_color, tmp);
			reflect = normalize(((float)(2.0 * dot(hit.normale, light_ray.dir)) * hit.normale) - light_ray.dir);
			tmp = dot(reflect, -scene.ray);
			if (tmp > 0)
				res_color = color_specular(scene, hit, light_hit, res_color, tmp);
		}
	}
	return (res_color);
}

static unsigned int		bounce(const t_scene scene, const t_hit old_hit, const int depth)
{
	int				i = depth;
	unsigned int	color = 0;
	float3			reflex = 0;
	t_hit			new_hit;
	while (i > 0)
	{
		reflex = normalize(scene.ray - (2 * (float)dot(old_hit.normale, scene.ray) * old_hit.normale));
		new_hit.dist = MAX_DIST;
		new_hit = ray_hit(old_hit.pos, reflex, scene);
		if (new_hit.dist > 0 && new_hit.dist < MAX_DIST)
		{
			new_hit.pos = (new_hit.dist * reflex) + old_hit.pos;
			new_hit.normale = get_hit_normale(scene, new_hit);
			new_hit.pos = new_hit.pos + ((new_hit.dist / 100) * new_hit.normale);
			color += 0.1 * phong2(new_hit, scene);
		}
		i--;
	}
	return (color);
}

static unsigned int	get_pixel_color(const t_scene scene)
{
	t_hit			hit;
	int				depth = PARAM->depth;
	unsigned int	color  = 0;
	unsigned int	bounce_color = 0;

	hit.dist = MAX_DIST;
	hit = ray_hit((ACTIVECAM.pos + PARAM->mvt), scene.ray, scene);
	if (hit.dist > 0 && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = (hit.dist * scene.ray) + (ACTIVECAM.pos + PARAM->mvt);
		hit.normale = get_hit_normale(scene, hit);
		hit.pos = hit.pos + ((hit.dist / 100) * hit.normale);
		color = phong(hit, scene);
		if (depth > 0)
			bounce_color = bounce(scene, hit, depth);
		return (color + bounce_color);
//		return (blend_add(color, 0.8*bounce_color));
	}
	return (get_ambient(scene, BACKCOLOR));
}

__kernel void	ray_trace(__global		char		*output,
						  				t_param		param,
						  __constant	t_cam		*cameras,
						  __constant	t_cone		*cones,
						  __constant	t_cylinder	*cylinders,
						  __constant	t_light		*lights,
						  __constant	t_plane		*planes,
						  __constant	t_sphere	*spheres,
						  __global		t_hit		*target_obj)
{
	t_scene		scene = grab_data(cameras, cones, cylinders, lights, planes, spheres, param);
	scene.pix.x = get_global_id(0);
	scene.pix.y = get_global_id(1);
	int			id = scene.pix.x + (PARAM->win_w * scene.pix.y); // NE PAS VIRER ID CAR BESOIN DANS MACRO OUTPUTE
	scene.ray = get_ray_cam(ACTIVECAM, scene, scene.pix.x ,scene.pix.y);
	if (scene.pix.x == PARAM->mou_x && scene.pix.y == PARAM->mou_y)
		*target_obj = ray_hit((ACTIVECAM.pos + PARAM->mvt), scene.ray, scene);
	OUTPUTE = get_pixel_color(scene);
}
