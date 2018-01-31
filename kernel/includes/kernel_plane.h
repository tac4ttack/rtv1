float		inter_plan(const t_plane plane, const float3 ray, const float3 origin)
{
	float	t;

	if ((t = dot(normalize(ray), normalize(plane.normale))) == 0)
		return (0);
	t = (dot(plane.pos - origin, normalize(plane.normale))) / t;
		if (t < 0.001)
		return (0);
	return (t);
}
