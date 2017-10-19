#include "kernel_header.h"

float3			sub_vect(float3 v1, float3 v2)
{
	float3		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

float3			add_vect(float3 v1, float3 v2)
{
	float3		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

float			norme_vect(float3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float3			normalize_vect(float3 v)
{
	float3		res;
	int			id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}

float			dot_vect(float3 v1, float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float3			mult_fvect(float m, float3 v)
{
	float3		res;

	res.x = m * v.x;
	res.y = m * v.y;
	res.z = m * v.z;
	return (res);
}

float3			get_abc(float radius, float3 ray, float3 origin)
{
	float3		abc;

	abc.x = dot_vect(ray, ray);
	abc.y = 2 * dot_vect(ray, origin);
	abc.z = dot_vect(origin, origin) - (radius * radius);
	return (abc);
}

float			inter_sphere(float radius, float3 ray, float3 cam_origin, float3 sphere_origin)
{
	float3		abc;
	float		d;
	float		res1;
	float		res2;

	cam_origin.x -= sphere_origin.x;
	cam_origin.y -= sphere_origin.y;
	cam_origin.z -= sphere_origin.z;
	abc = get_abc(radius, ray, cam_origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (1000000000);
	if (d == 0)
		return ((-abc[1]) / (2 * abc[0]));
	res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
	res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	if (res1 < res2)
		return(res1);
	return(res2);
}

float			inter_plan(float3 plan_origin, float3 plan_normale, float3 ray, float3 cam_origin)
{
	float		t;

	t = dot_vect(ray, plan_normale);
	
	t = dot_vect(sub_vect(plan_origin, cam_origin), plan_normale) / t;
	if (t < 0.0000001)
		return (1000000000);
	return (t);
}

float			modh_vect(int x)
{
	return ((float)((float)x - (WINX / 2.0)) / (WINX / 2.0));
}

float			modv_vect(int y)
{
	return ((float)(((float)y - (WINY / 2.0)) / (WINY / 2.0) * WINY / WINX));
}

float3			get_ray(float3 n, float3 v, float3 h, int x, int y)
{
	float3		res;

	h = mult_fvect(modh_vect(x), h);
	v = mult_fvect(modv_vect(y), v);
	res = add_vect(n, v);
	res = add_vect(res, h);
	return (res);
}

__kernel void	ray_trace(__global char *output,
							float mvx,
							float mvy,
							float mvz,
							__constant t_object *scene)
{
	int		id = get_global_id(0);
	int		x = id % WINX;
	int		y = id / WINX;

	// CAM
	float3	cam_origin;
	cam_origin.x = 0 + mvx;
	cam_origin.y = 0 + mvy;
	cam_origin.z = 0 + mvz;
	float3	hor;
	hor.x = 0.6;
	hor.y = 0;
	hor.z = 0;
	float3	vert;
	vert.x = 0;
	vert.y = 0.6;
	vert.z = 0;
	float3	cam_dir;
	cam_dir.x = 0;
	cam_dir.y = 0;
	cam_dir.z = 1;

	// SPHERE
	float3	boule_origin;
	boule_origin.x = 0;
	boule_origin.y = 10;
	boule_origin.z = 200;
	float	radius = 10;

	// SPHERE2
	float3	boule_origin2;
	boule_origin2.x = 0;
	boule_origin2.y = -10;
	boule_origin2.z = 50;
	float	radius2 = 10;

	// PLANE
	float3	plan_origin;
	plan_origin.x = 0;
	plan_origin.y = 0;
	plan_origin.z = 300;
	float3	plan_normale;
	plan_normale.x = 0;
	plan_normale.y = -1;
	plan_normale.z = 0;

	float plan;
	float sphere;
	float sphere2;

	float3 ray = get_ray(cam_dir, vert, hor, x ,y);
	if (( plan = inter_plan(plan_origin, plan_normale, ray, cam_origin)) < 0)
		plan = 1000000000;
	if (( sphere= inter_sphere(radius, ray, cam_origin, boule_origin)) < 0)
		sphere = 1000000000;
	if ((sphere2 = inter_sphere(radius2, ray, cam_origin, boule_origin2)) < 0)
		sphere2 = 1000000000;
	if (sphere == 1000000000 && plan == 1000000000 && sphere2 == 1000000000)
		OUTPUTE = BACKCOLOR;
	else if (sphere < plan && sphere < sphere2)
		OUTPUTE = SCOLOR;
	else if (sphere2 < sphere && sphere2 < plan)
		OUTPUTE = SSCOLOR;
	else
		OUTPUTE = PCOLOR;
}
