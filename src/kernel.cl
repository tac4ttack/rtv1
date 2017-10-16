#define WINX 1920
#define WINY 1080
#define BACKCOLOR 0x00000000
#define SCOLOR 0x000000FF
#define PCOLOR 0x00FF0000

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

float			inter_sphere(float radius, float3 ray, float3 origin)
{
	float3		abc;
	float		d;
	float		res1;
	float		res2;

	abc = get_abc(radius, ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (-1.0);
	res1 = -(abc[1] + sqrt(d));
	res2 = -(abc[1] - sqrt(d));
	if (res1 < res2)
		return(res1);
	return(res2);
}

float			inter_plan(float3 plan_origin, float3 plan_normale, float3 ray, float3 cam_origin)
{
	float		t;

	t = dot_vect(ray, plan_normale);
	if (t < 0.0000001)
		return (-1.0);
	t = dot_vect(sub_vect(plan_origin, cam_origin), plan_normale) / t;
	if (t < 0)
		return (-1.0);
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

__kernel void	ray_trace(__global char *output)
{
	float3	cam_origin;
	float3	boule_origin;
	float3	direction_base;
	float	radius = 2;
	float3	ray;
	float3	hor;
	float3	vert;
	float3	cam_dir;

//plan
	float3	plan_origin;
	float3	plan_normale;

	int		id = get_global_id(0);
	int		x = id % WINX;
	int		y = id / WINX;

	hor.x = 0.6;
	hor.y = 0;
	hor.z = 0;
	vert.x = 0;
	vert.y = 0.6;
	vert.z = 0;
	cam_dir.x = 0;
	cam_dir.y = 0;
	cam_dir.z = 1;

	boule_origin.x = 0;
	boule_origin.y = 0;
	boule_origin.z = 0;
	plan_origin.x = -100;
	plan_origin.y = 0;
	plan_origin.z = 0;
	plan_normale.x = 0;
	plan_normale.y = 0;
	plan_normale.z = 1;
	cam_origin.x = 0;
	cam_origin.y = 0;
	cam_origin.z = -10;
	ray = get_ray(cam_dir, vert, hor, x ,y);
	float plan = inter_plan(plan_origin, plan_normale, ray, cam_origin);
	float sphere = inter_sphere(radius, ray, cam_origin);
	if (plan < 0 && sphere < 0)
		((__global unsigned int *)output)[id] = BACKCOLOR;
	else if (plan < sphere)
		((__global unsigned int *)output)[id] = PCOLOR;
	else
		((__global unsigned int *)output)[id] = SCOLOR;
}
