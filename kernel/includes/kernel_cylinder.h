static float3	get_cylinder_abc(const float radius, const float3 dir, const float3 ray, const float3 origin)
{
	float3		abc;

	// SEMBLE OK
	abc.x = dot(ray, ray) - (dot(ray, dir) * dot(ray, dir));
	abc.y = 2 * (dot(ray, origin) - (dot(ray, dir) * dot(origin, dir)));
	abc.z = dot(origin, origin) - (dot(origin, dir) * dot(origin, dir)) - (radius * radius);
	return (abc);
}

float			inter_cylinder(float height, float3 dir, float radius, float3 pos, float3 ray, float3 origin)
{
	float3		abc = 0;
//	float3		dir = rotate_obj(cyl.dir, cyl.pitch, cyl.yaw, 0);
	float		d = 0;
	float		res1 = 0;
	float		res2 = 0;
	float		m = 0;

	origin -= pos;
	abc = get_cylinder_abc(radius, dir, ray, origin);
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
		if (height == 0 || (dot(ray, dir) * res1 +
			dot(origin, dir) < height && dot(ray, dir) * res1 +
			dot(origin, dir) > 0))
			return (res1);
	}
	if (height ==  0 || (dot(ray, dir) * res2 +
			dot(origin, dir) < height && dot(ray, dir) * res2 +
			dot(origin, dir) > 0))
		return (res2);
	else
		return (0);
}
