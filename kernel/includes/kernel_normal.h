float3			compute_cone_normal(const t_scene scene, const t_hit hit)
{
	float3		normal = 0;
	float		k = 0;
	
	k = CONES[hit.id].angle * DEG2RAD;
	k = tan(k);
	k = 1 + k * k;
	normal = dot(-scene.ray, normalize(CONES[hit.id].dir)) * hit.dist - dot(ACTIVECAM.pos + PARAM->mvt - CONES[hit.id].pos, normalize(CONES[hit.id].dir));
	normal = ((hit.pos - normalize(CONES[hit.id].pos)) - (k * normalize(CONES[hit.id].dir) * normal)) * -1;
	return (normal);
}

float3			compute_cylinder_normal(const t_scene scene, const t_hit hit)
{
	float3		normal = 0;

	normal = hit.pos - CYLIND[hit.id].pos;
	normal.z = 0;	// fonctionne pour cylindre aligné en Z
	return (normal);
}

float3			compute_plane_normal(const t_scene scene, const t_hit hit)
{
	float3		normal = 0;

	if (dot(PLANE[hit.id].normale, -scene.ray) < 0)
		normal = -PLANE[hit.id].normale;
	else
		normal = PLANE[hit.id].normale;
	return (normal);
}

float3			compute_sphere_normal(const t_scene scene, const t_hit hit)
{
	float3		normal = 0;

	normal = hit.pos - SPHERE[hit.id].pos;
	return (normal);
}

float3			compute_hit_normale(const t_scene scene, const t_hit hit)
{
	if (hit.type == 1)
		return (compute_cone_normal(scene, hit));
	else if (hit.type == 2)
		return (compute_cylinder_normal(scene, hit));
	else if (hit.type == 4)
		return (compute_plane_normal(scene, hit));
	else
		return (compute_sphere_normal(scene, hit));
}