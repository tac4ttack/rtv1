#include "kernel_header.h"
#include "kernel_color.h"
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
		return (res1);
	return (res2);
}

float3					get_cylinder_abc(float radius, float3 dir, float3 ray, float3 origin)
{
	float3		abc;

	abc.x = dot_vect(ray, ray) - (dot_vect(ray, dir) * dot_vect(ray, dir));
	abc.y = 2 * (dot_vect(ray, origin) - (dot_vect(ray, dir) * dot_vect(origin, dir)));
	abc.z = dot_vect(origin, origin) - (dot_vect(origin, dir) * dot_vect(origin, dir)) - (radius * radius);
	return (abc);
}

float					inter_cylinder(t_cylinder cylind, float3 ray, float3 origin)
{
	float3				abc;
	float				d;
	float				res1;
	float				res2;

	origin -= cylind.pos;
	abc = get_cylinder_abc(cylind.radius, normalize(cylind.dir), ray, origin);
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
		if (cylind.height == 0 || (dot_vect(ray, normalize(cylind.dir) * res1 +
			dot_vect(origin, normalize(cylind.dir))) < cylind.height && dot_vect(ray, normalize(cylind.dir) * res1 +
			dot_vect(origin, normalize(cylind.dir))) > 0))
			return (res1);
	}
	if (cylind.height ==  0 || (dot_vect(ray, normalize(cylind.dir) * res2 +
			dot_vect(origin, normalize(cylind.dir))) < cylind.height && dot_vect(ray, normalize(cylind.dir) * res2 +
			dot_vect(origin, normalize(cylind.dir))) > 0))
		return (res2);
	else
		return (0);
}

float3					get_cone_abc(t_cone cone, float3 ray, float3 origin)
{
	float3		abc;
	float		k = cone.angle * DEG2RAD;
	k = tan(k);
	k = 1 + k * k;

	abc.x = dot_vect(ray, ray) - (k * (dot_vect(ray, cone.dir) * dot_vect(ray, cone.dir)));
	abc.y = 2 * (dot_vect(ray, origin) - (k * \
			(dot_vect(ray, cone.dir) * dot_vect(origin, cone.dir))));
	abc.z = (dot_vect(origin, origin) - \
			(k * (dot_vect(origin, cone.dir) * dot_vect(origin, cone.dir))));
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

	if ((t = dot_vect(normalize(ray), normalize(plane.normale))) == 0)
		return (0);
	t = (dot_vect(plane.pos - origin, normalize(plane.normale))) / t;
		if (t < 0.001)
		return (0);
	return (t);
}

unsigned int			light_angle(float angle, unsigned int obj_color, t_scene scene)
{
	unsigned int		r = (obj_color & 0x00FF0000) >> 16;
	unsigned int		g = (obj_color & 0x0000FF00) >> 8;
	unsigned int		b = (obj_color & 0x000000FF);
	float				mult = scene.param->bloom * angle;

	//if (angle <= 0)
	//	return (obj_color);
	if (mult > r)
		r = 0;
	else if ((r -= mult) > 255)
		r = 255;
	if (mult > g)
		g = 0;
	else if ((g -= mult) > 255)
		g = 255;
	if (mult > b)
		b = 0;
	else if ((b -= mult) > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

float					light_angelamerkel(t_hit hit, t_light_ray light_ray)
{
	float				cos_angela;
	float				angela;

	cos_angela = dot_vect(light_ray.dir, hit.normale) / (norme_vect(light_ray.dir) * norme_vect(hit.normale));
	angela = acos(cos_angela) * RAD2DEG;
	//printf("%f\n", angela);
	return (angela);
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
//	printf("dist = %i\n", PARAM->n_cones);
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
		//		printf("weeeee");
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
		res = dot_vect(scene.ray, normalize(CONES[hit.id].dir)) * \
			hit.dist - dot_vect(ACTIVECAM.pos + PARAM->mvt - CONES[hit.id].pos, normalize(CONES[hit.id].dir));
		res = (hit.pos - normalize(CONES[hit.id].pos)) - (k * normalize(CONES[hit.id].dir) * res);
	//	if (dot_vect(CONES[hit.id].pos - hit.pos, normalize(CONES[hit.id].dir)) > 0)
			res = -res;
	}
	else if (hit.type == 2)
	{
		res = dot_vect(scene.ray, normalize(CYLIND[hit.id].dir) * hit.dist + \
			dot_vect(ACTIVECAM.pos + PARAM->mvt - CYLIND[hit.id].pos, normalize(CYLIND[hit.id].dir)));
		res = (hit.pos - CYLIND[hit.id].pos) - (normalize(CYLIND[hit.id].dir) * res);
	}
	else if (hit.type == 4) // bizarrement on fait l'inverse de ce qu'on peut voir dans le code d'autres personnes
	{
		if (dot_vect(PLANE[hit.id].normale, scene.ray) < 0)
			res = PLANE[hit.id].normale;
		else
			res = -PLANE[hit.id].normale;
	}
	else if (hit.type == 5)
		res = hit.pos - SPHERE[hit.id].pos;
	return (normalize(res));
}


unsigned int			light(t_hit hit, t_scene scene)
{
	int					i = -1;
	float				angle = 0;
	t_light_ray			light_ray;
	t_hit				light_hit;
	unsigned int		obj_color = get_obj_hue(scene, hit);
	unsigned int		ambient_color = blend_ambiant(obj_color);
	unsigned int		res_color = 0;
	unsigned int		tmp_color = 0;

	//	printf("%u\n", obj_color);
	while (++i < PARAM->n_lights)
	{
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = norme_vect(light_ray.dir);
		light_ray.dir = normalize(light_ray.dir);
		light_hit = ray_hit(hit.pos, light_ray.dir, scene);
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		;//	printf("%f\n", light_hit.dist);
		else
		{
			angle = light_angelamerkel(hit, light_ray);
			if ((tmp_color = light_angle(angle, obj_color, scene)) < ambient_color)
				tmp_color = ambient_color;
			res_color = blend_add(res_color, tmp_color);
		}
	}
	if (res_color == 0)
		res_color = ambient_color;
	return (res_color);
}

unsigned int			phong(t_hit hit, t_scene scene)
{
	int					i = -1;
	unsigned int		obj_color = get_obj_hue(scene, hit);
	unsigned int		ambient_color = get_ambient(obj_color, scene);
	unsigned int		res_color = ambient_color;
	float				tmp;
	float3				tmp2;
	t_light_ray			light_ray;
	t_hit				light_hit;

	float				angle = 0;
	unsigned int		tmp_color = 0;

	//	printf("%u\n", obj_color);
	while (++i < PARAM->n_lights)
	{
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = norme_vect(light_ray.dir);
		light_ray.dir = normalize(light_ray.dir);
		light_hit = ray_hit(hit.pos, light_ray.dir, scene);
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		;//	printf("%f\n", light_hit.dist);
		else
		{
		tmp = dot_vect(hit.normale, light_ray.dir);
		if (tmp > 0)
			res_color = color_diffuse(hit, scene, res_color, tmp);
		tmp = dot_vect(hit.normale, -light_ray.dir);
		if (tmp > 0)
			res_color = color_specular(hit, scene, res_color, tmp);
		}
	}
//	if (res_color == 0)
//		res_color = ambient_color;
	
	return (res_color);
}

unsigned int	get_pixel_color(t_scene scene)
{
	t_hit		hit;
	float		bias = 0.000001;

	hit.dist = MAX_DIST;
	hit = ray_hit((ACTIVECAM.pos + PARAM->mvt), scene.ray, scene);
//	if (hit.dist > 0)
	if (hit.dist > 0 && hit.dist < MAX_DIST) // ajout d'une distance max pour virer acnee
	{
		hit.pos = mult_fvect(hit.dist, scene.ray) + (ACTIVECAM.pos + PARAM->mvt);
		hit.normale = get_hit_normale(scene, hit);
//		if (hit.type == 4)
//			hit.pos = hit.pos + ((bias + hit.dist / 5) * hit.normale);
//		else
			hit.pos = hit.pos + ((/*bias +  BIAS INUTILE MAINTENANT?*/hit.dist / 100) * hit.normale);
//		return (light(hit, scene));
		return (phong(hit, scene));
	}
//	return (BACKCOLOR);
//	return (((unsigned int)PARAM->ambient.x << 16) + \
			((unsigned int)PARAM->ambient.y << 8) +  \
			(unsigned int)PARAM->ambient.z); 
	return (get_ambient(BACKCOLOR, scene)); // renvoie la couleur de fond selon lumiere ambiante
}

// OLD CAN BE DELETED
/*float3					get_ray_cam(t_cam cam, int x, int y)
{
	float3				ray;
	float3				h = mult_fvect(modh_vect(x), cam.hor);
	float3				v = mult_fvect(modv_vect(y), cam.ver);

	ray = normalize(cam.dir) + v + h;
	return (normalize(ray));
}
*/

float3						get_ray_cam(t_cam cam, t_scene scene, int x, int y)
{
	float3					cam_ray = 0;
	float					ratio = (float)PARAM->win_w / (float)PARAM->win_h;
	cam_ray.x += ((2 * ((x + 0.5) / PARAM->win_w)) - 1) * ratio * (tan((cam.fov / 2) * DEG2RAD));
//	cam_ray.x += sin(cam_ray.x * 10) / 10.0; // deformation kikoolol
	cam_ray.y += ((1 - (2 * ((y + 0.5) / PARAM->win_h))) * tan((cam.fov / 2) * DEG2RAD));
	cam_ray.z = cam.dir.z;
	return(normalize(cam_ray));
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
	int		id = x + (PARAM->win_w * y); // NE PAS VIRER ID CAR BESOIN DANS MACRO OUTPUTE
	scene.ray = get_ray_cam(ACTIVECAM, scene, x ,y);
	OUTPUTE = get_pixel_color(scene);
}
