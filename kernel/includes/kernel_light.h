unsigned int			phong(t_hit hit, t_scene scene)
{
	int					i = -1;
	unsigned int		res_color = get_ambient(scene, get_obj_hue(scene, hit));
	float				tmp;
	float3				reflect = 0;

	t_light_ray			light_ray;
	t_hit				light_hit = hit_init();

	while (++i < PARAM->n_lights)
	{
		tmp = 0;
		light_ray.dir = LIGHT[i].pos - hit.pos;
		light_ray.dist = length(light_ray.dir);
		light_ray.dir = normalize(light_ray.dir);
		light_hit = ray_hit(hit.pos, light_ray.dir, scene);
		light_hit.id = i;
		light_hit.type = 3;
		if (light_hit.dist < light_ray.dist && light_hit.dist > 0)
		;
		else
		{
			tmp = dot(hit.normale, light_ray.dir);
		//	if ((scene.pix.x == 175 || scene.pix.x == 525 || scene.pix.x == 845) && scene.pix.y == 370)
		//		printf("light.id = %d | light.color = %08x\n", light_hit.id, LIGHT[light_hit.id].color);
		//		printf("l_hit.id = %d l_hit.type = %d l_hit.dist = %f\n", light_hit.id, light_hit.type, light_hit.dist);
			if (tmp > 0)
				res_color = color_diffuse(scene, hit, light_hit, res_color, tmp);
			reflect = normalize(mult_fvect(2.0 * dot(hit.normale, light_ray.dir), hit.normale) - light_ray.dir);
			tmp = dot(reflect, -scene.ray);
			if (tmp > 0)
				res_color = color_specular(scene, hit, light_hit, res_color, tmp);
		}
	}
	return (res_color);
}
