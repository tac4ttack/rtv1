t_scene			grab_data(__constant t_cam *cameras, \
						  __constant t_cone *cones, \
						  __constant t_cylinder *cylinders, \
						  __constant t_light *lights, \
						  __constant t_plane *planes, \
						  __constant t_sphere *spheres, \
						  t_param param)
{
t_scene	result;

result.cameras = &cameras;
result.cones = &cones;
result.cylinders = &cylinders;
result.lights = &lights;
result.planes = &planes;
result.spheres = &spheres;
result.param = &param;
return (result);
}

int				get_max_obj(t_param *param)
{
	int			res = param->n_cones;
	if (param->n_cylinders > res)
		res = param->n_cylinders;
	if (param->n_planes > res)
		res = param->n_planes;
	if (param->n_spheres > res)
		res = param->n_spheres;
	return (res);
}
