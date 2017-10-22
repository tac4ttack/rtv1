#include "kernel_header.h"

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
	if ((res1 < res2 && res1 > 0) || (res1 > res2 && res2 < 0))
		return(res1);
	return(res2);
}

float			inter_plan(float3 plan_origin, float3 plan_normale, float3 ray, float3 cam_origin)
{
	float		t;

	t = dot_vect(ray, plan_normale);
	t = dot_vect(sub_vect(plan_origin, cam_origin), plan_normale) / t;
	if (t < 0.00001)
		return (1000000000);
	return (t);
}

float3			get_ray(float3 dir, float3 v, float3 h, int x, int y)
{
	float3		res;

	h = mult_fvect(modh_vect(x), h);
	v = mult_fvect(modv_vect(y), v);
	res = add_vect(dir, v);
	res = add_vect(res, h);
	return (res);
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

unsigned int			light_sphere(char obj, float3 p, float3 boule_origin, float radius, float3 light_origin, float3 plan_origin, float3 plan_normale)
{
	float3		normale = p - boule_origin;
	float3		lightray = light_origin - p;
	float		lightdist = norme_vect(lightray);
	float3		lightdir = normalize_vect(lightray);
	float cos_angle;
	float plan;
	float sphere;
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
	return (light_angle(angle));
}



__kernel void	ray_trace(__global char *output,
							float3 mvt,
							t_scene scene,
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

//	transmission test
//	if (id < 5)
//		printf("%d\n", scene.n_spheres);

	// CAM
	float3	cam_origin;
	cam_origin.x = 0 + mvt.x;
	cam_origin.y = 0 + mvt.y;
	cam_origin.z = 0 + mvt.z;
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
	boule_origin.y = 0;
	boule_origin.z = 20;
	float	radius = 2;

	// SPHERE2
	float3	boule_origin2;
	boule_origin2.x = 0;
	boule_origin2.y = -10;
	boule_origin2.z = 50;
	float	radius2 = 10;

	// LIGHT
	float3	light_origin;
	light_origin.x = 0;
	light_origin.y = -20;
	light_origin.z = 20;
	float	radiusl = 1;

	// PLANE
	float3	plan_origin;
	plan_origin.x = 0;
	plan_origin.y = 10;
	plan_origin.z = 0;
	float3	plan_normale;
	plan_normale.x = 0;
	plan_normale.y = 1;
	plan_normale.z = 0;

	normalize_vect(plan_normale);

	float plan;
	float sphere;
	float light;

	float3 ray = get_ray(cam_dir, vert, hor, x ,y);
	if (( plan = inter_plan(plan_origin, plan_normale, ray, cam_origin)) < 0)
		plan = 1000000000;
	if (( sphere = inter_sphere(radius, ray, cam_origin, boule_origin)) < 0)
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
}
