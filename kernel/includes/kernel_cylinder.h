static float3	get_cylinder_abc(const float radius, const float3 dir, const float3 ray, const float3 origin)
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
	float				res1 = 0;
	float				res2 = 0;
	float				m;

	origin -= cylind.pos;
	abc = get_cylinder_abc(cylind.radius, normalize(cylind.dir), ray, origin);
	d = (abc.y * abc.y) - (4 * (abc.x * abc.z));
	if (d < 0)
		return (0);
	if (d == 0)
		res1 = (-abc[1]) / (2 * abc[0]);
	else
	{
		res1 = (((-abc[1]) + sqrt(d)) / (2 * abc[0]));
		res2 = (((-abc[1]) - sqrt(d)) / (2 * abc[0]));
	}
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

float3			get_cylinder_normal(t_scene scene, t_hit hit)
{
	float3 res = 0;
	float3 v = 0;
	float3 project = 0;
	float doty = 0;

//	v = hit.pos - CYLIND[hit.id].pos;
//	doty = dot(v, normalize(CYLIND[hit.id].dir));
//	project = doty * normalize(CYLIND[hit.id].dir);
//	res = v - project;

	v = hit.pos - CYLIND[hit.id].pos;
//	if (scene.pix.x == scene.param->win_w / 2 && scene.pix.y == scene.param->win_h / 2)
//		printf("toto caca");
//	printf("%d %d\n", scene.pix.x, scene.pix.y);
	doty = dot(v, normalize(CYLIND[hit.id].dir));
	project = doty * normalize(CYLIND[hit.id].dir);
	res = v - project;
	return (normalize(res));
}
