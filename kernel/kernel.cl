#include "kernel_header.h"
#include "kernel_color.h"
#include "kernel_data.h"
#include "kernel_vector.h"
#include "kernel_debug.h"

float3						rotat_vect(float3 vect, float pitch, float yaw, float roll)
{
	float3					res;
	float					rad_pitch = pitch * DEG2RAD;
	float					rad_yaw = yaw * DEG2RAD;
	float					rad_roll = roll * DEG2RAD;

	res.x = vect.x * cos(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_pitch) * -sin(rad_roll) + cos(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) + vect.z * (-sin(rad_roll) * -sin(rad_pitch) + cos(rad_roll) * sin(rad_yaw) * cos(rad_pitch));
	res.y = vect.x * sin(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_roll) * cos(rad_pitch) + sin(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) + vect.z * (cos(rad_roll) * -sin(rad_pitch) + sin(rad_roll) * sin(rad_yaw) * cos(rad_pitch));
	res.z = vect.x * -sin(rad_yaw) + vect.y * cos(rad_yaw) * sin(rad_pitch) + vect.z * cos(rad_yaw) * cos(rad_pitch);
	return (res);
}

float3					get_sphere_abc(float radius, float3 ray, float3 origin)
{
	float3		abc;

	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, origin);
	abc.z = dot(origin, origin) - (radius * radius);
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
		return (res1);
	return (res2);
}

float3					get_cylinder_abc(float radius, float3 dir, float3 ray, float3 origin)
{
	float3		abc;

	// SEMBLE OK
	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir)) - (radius * radius);
	return (abc);
}

float					inter_cylinder(t_cylinder cylind, float3 ray, float3 origin)
{
	float3				abc;
	float				d;
	float				res1;
	float				res2;

	origin -= cylind.pos;
	abc = get_cylinder_abc(cylind.radius, rotat_vect(fast_normalize(cylind.dir), cylind.pitch, cylind.yaw, cylind.roll), ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		return ((-abc[1]) / (2 * abc[0]));
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if (res1 < 0 && res2 < 0)
		return (0);
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
	{
		if (cylind.height == 0 || (dot(ray, fast_normalize(cylind.dir) * res1 +
			dot(origin, fast_normalize(cylind.dir))) < cylind.height && dot(ray, fast_normalize(cylind.dir) * res1 +
			dot(origin, fast_normalize(cylind.dir))) > 0))
			return (res1);
	}
	if (cylind.height ==  0 || (dot(ray, fast_normalize(cylind.dir) * res2 +
			dot(origin, fast_normalize(cylind.dir))) < cylind.height && dot(ray, fast_normalize(cylind.dir) * res2 +
			dot(origin, fast_normalize(cylind.dir))) > 0))
		return (res2);
	else
		return (0);
}

float3					get_cone_abc(t_cone cone, float3 ray, float3 origin)
{
	float3		abc = 0;
	float		k = cone.angle * DEG2RAD;
	k = tan(k);
	k = 1 + k * k;

	abc.x = dot(ray, ray) - (k * (dot(ray, cone.dir) * dot(ray, cone.dir)));
	abc.y = 2 * (dot(ray, origin) - (k * \
			(dot(ray, cone.dir) * dot(origin, cone.dir))));
	abc.z = (dot(origin, origin) - \
			(k * (dot(origin, cone.dir) * dot(origin, cone.dir))));
	return (abc);
}

float					inter_cone(t_cone cone, float3 ray, float3 origin)
{
	float3				abc;
	float				d;
	float				res1;
	float				res2;
	float				res;

	origin -= cone.pos;
	abc = get_cone_abc(cone, ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		res = (-abc[1]) / (2 * abc[0]);
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		res = res1;
	else
		res = res2;
	return (res);
}

float					inter_plan(t_plane plane, float3 ray, float3 origin)
{
	float				t;

	if ((t = dot(fast_normalize(ray), fast_normalize(plane.normale))) == 0)
		return (0);
	t = (dot(plane.pos - origin, fast_normalize(plane.normale))) / t;
		if (t < 0.001)
		return (0);
	return (t);
}

t_hit			ray_hit(float3 origin, float3 ray, t_scene scene)
{
	unsigned int			i = 0;
	int			max = get_max_obj(PARAM);
	t_hit		hit;
	float		dist = 0;

	hit.dist = 0;
	hit.type = 0;
	hit.id = 0;
	hit.pos = (0, 0, 0);
	hit.normale = (0, 0, 0);
	while (i < max)
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
		i++;
	}
	return (hit);
}

float3			get_hit_normale(t_scene scene, t_hit hit)
{
	float3		res;

	if (hit.type == 1)
	{
		float k = CONES[hit.id].angle * DEG2RAD;
		k = tan(k);
		k = 1 + k * k;
		res = dot(-=scene.ray, fast_normalize(CONES[hit.id].dir)) * \
			hit.dist - dot(ACTIVECAM.pos + PARAM->mvt - CONES[hit.id].pos, fast_normalize(CONES[hit.id].dir));
		res = ((hit.pos - fast_normalize(CONES[hit.id].pos)) - (k * fast_normalize(CONES[hit.id].dir) * res)) * -1;
	}
	else if (hit.type == 2)
	{
		res = dot(-scene.ray, fast_normalize(CYLIND[hit.id].dir) * hit.dist + \
			dot(ACTIVECAM.pos + PARAM->mvt - CYLIND[hit.id].pos, fast_normalize(CYLIND[hit.id].dir)));
		res = hit.pos - CYLIND[hit.id].pos - (fast_normalize(CYLIND[hit.id].dir) * res);
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
	return (fast_normalize(res));
}

unsigned int			phong(t_hit hit, t_scene scene)
{
	int					i = -1;
	unsigned int		obj_color = get_obj_hue(scene, hit);
	unsigned int		ambient_color = get_ambient(obj_color, scene);
	unsigned int		res_color = ambient_color;
	float				tmp;
	float3				reflect = 0;
	t_light_ray			light_ray;
	t_hit				light_hit;

	while (++i < PARAM->n_lights)
	{
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = fast_length(light_ray.dir);
		light_ray.dir = fast_normalize(light_ray.dir);
		light_hit = ray_hit(hit.pos, light_ray.dir, scene);
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		;
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
			if (tmp > 0)
				res_color = color_diffuse(hit, scene, res_color, tmp);
			reflect = fast_normalize(mult_fvect(2.0 * dot(hit.normale, light_ray.dir), hit.normale) - light_ray.dir);
			tmp = dot(reflect, -scene.ray);
			if (tmp > 0)
				res_color = color_specular(hit, scene, res_color, tmp);
		}
	}

	return (res_color);
}

unsigned int	get_pixel_color(t_scene scene)
{
	t_hit		hit;
	float		bias = 0.000001;

	hit.dist = MAX_DIST;
	hit = ray_hit((ACTIVECAM.pos + PARAM->mvt), scene.ray, scene);
	if (hit.dist > 0 && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee mais pas fiable a 100%
	{
		hit.pos = mult_fvect(hit.dist, scene.ray) + (ACTIVECAM.pos + PARAM->mvt);
		hit.normale = get_hit_normale(scene, hit);
		hit.pos = hit.pos + ((bias +  hit.dist / 100) * hit.normale);
		return (phong(hit, scene));
	}
	return (get_ambient(BACKCOLOR, scene));
}


float3						get_ray_cam(t_cam cam, t_scene scene, int x, int y)
{
	float3					cam_ray = 0;
	float					ratio = (float)PARAM->win_w / (float)PARAM->win_h;
	cam_ray.x = ((2 * ((x + 0.5) / PARAM->win_w)) - 1) * ratio * (tan((cam.fov / 2) * DEG2RAD));
	cam_ray.y = ((1 - (2 * ((y + 0.5) / PARAM->win_h))) * tan((cam.fov / 2) * DEG2RAD));
	cam_ray.z = 1;
	cam_ray = rotat_vect(cam_ray, cam.pitch, cam.yaw, 0);
	return(fast_normalize(cam_ray));
}

__kernel void	ray_trace(__global char *output,
						  t_param param,
						  __constant t_cam *cameras,
						  __constant t_cone *cones,
						  __constant t_cylinder *cylinders,
						  __constant t_light *lights,
						  __constant t_plane *planes,
						  __constant t_sphere *spheres)
{
	t_scene scene = grab_data(cameras, cones, cylinders, lights, planes, spheres, param);
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	int		id = x + (PARAM->win_w * y);
	scene.ray = get_ray_cam(ACTIVECAM, scene, x ,y);
	OUTPUTE = get_pixel_color(scene);
}
