t_scene			grab_data(const __constant t_cam *cameras, \
						const __constant t_cone *cones, \
						const __constant t_cylinder *cylinders, \
						const __constant t_light *lights, \
						const __constant t_plane *planes, \
						const __constant t_sphere *spheres, \
						const t_param param)
{
t_scene	result;

result.cameras = cameras;
result.cones = cones;
result.cylinders = cylinders;
result.lights = lights;
result.planes = planes;
result.spheres = spheres;
result.param = &param;
return (result);
}

t_hit			hit_init(void)
{
	t_hit		hit;

	hit.dist = 0.0;
	hit.type = 0;
	hit.id = 0;
	hit.pos = 0.0;
	hit.normale = 0.0;
	return (hit);
}

int				get_max_obj(const t_param *param)
{
	unsigned int			res = param->n_cones;

	if (param->n_cylinders > res)
		res = param->n_cylinders;
	if (param->n_planes > res)
		res = param->n_planes;
	if (param->n_spheres > res)
		res = param->n_spheres;
	return (res);
}
