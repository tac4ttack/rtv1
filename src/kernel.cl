#define WINX 1920
#define WINY 1080
#define BACKCOLOR 0x00000000
#define OBJCOLOR 0x000000FF

float3			sub_vect(float3 v1, float3 v2)
{
	float3		res;

	res[0] = v1[0] - v2[0];
	res[1] = v1[1] - v2[1];
	res[2] = v1[2] - v2[2];
	return (res);
}

float3			add_vect(float3 v1, float3 v2)
{
	float3		res;

	res[0] = v1[0] + v2[0];
	res[1] = v1[1] + v2[1];
	res[2] = v1[2] + v2[2];
	return (res);
}

float			norme_vect(float3 v)
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

float3			normalize_vect(float3 v)
{
	float3		res;
	int			id = 1 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

	res[0] = v[0] * id;
	res[1] = v[1] * id;
	res[2] = v[2] * id;
	return (res);
}

float			dot_vect(float3 v1, float3 v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

float3			mult_fvect(float m, float3 v)
{
	float3		res;

	res[0] = m * v[0];
	res[1] = m * v[1];
	res[2] = m * v[2];
	return (res);
}

float3			get_abc(float radius, float3 ray, float3 origin)
{
	float3		abc;

	abc[0] = dot_vect(ray, ray);
	abc[1] = 2 * dot_vect(ray, origin);
	abc[2] = dot_vect(origin, origin) - (radius * radius);
	return (abc);
}

int				inter_sphere(float radius, float3 ray, float3 origin)
{
	float3		abc;
	float		d;

	abc = get_abc(radius, ray, origin);
	d = (abc[1] * abc[1]) - (4 * (abc[0] * abc[2]));
	if (d < 0)
		return (0);
	else
		return (1);
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
	float	radius = 1;
	float3	ray;
	float3	hor;
	float3	vert;
	float3	cam_dir;

	int		id = get_global_id(0);
	int		x = id % WINX;
	int		y = id / WINX;

	hor[0] = 0.6;
	hor[1] = 0;
	hor[2] = 0;
	vert[0] = 0;
	vert[1] = 0.6;
	vert[2] = 0;
	cam_dir[0] = 0;
	cam_dir[1] = 0;
	cam_dir[2] = 1;

	boule_origin[0] = 0;
	boule_origin[1] = 0;
	boule_origin[2] = 0;
	cam_origin[0] = 0;
	cam_origin[1] = 0;
	cam_origin[2] = -10;
	ray = get_ray(cam_dir, vert, hor, x ,y);
	if (inter_sphere(radius, ray, cam_origin) == 0)
		((__global unsigned int *)output)[id] = BACKCOLOR;
	else
		((__global unsigned int *)output)[id] = OBJCOLOR;
}
