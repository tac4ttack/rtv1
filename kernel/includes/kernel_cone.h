static float3	get_cone_abc(const t_cone cone, const float3 ray, const float3 origin)
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

float			inter_cone(const t_cone cone, const float3 ray, float3 origin)
{	
	float3		abc = 0;
	float		d = 0;
	float		res1 = 0;
	float		res2 = 0;
	float		res = 0;

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
