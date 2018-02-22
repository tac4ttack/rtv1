float		inter_plan(const __local t_scene *scene, const int id, const float3 ray, const float3 origin)
{
	float	t;

	t = dot(normalize(ray), normalize(PLANE[id].normale));
	if (fabs(t) < 0.0005)
		return (0);
	t = (dot(PLANE[id].pos - origin, normalize(PLANE[id].normale))) / t;
		if (t < 0.001)
		return (0);
	return (t);
}
