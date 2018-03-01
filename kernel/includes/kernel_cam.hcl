#ifndef KERNEL_CAM_HCL
# define KERNEL_CAM_HCL

float3						get_ray_cam(__local t_scene *scene, const uint2 pix)
{
	float3					cam_ray = 0;
	float					ratio = (float)scene->win_w / (float)scene->win_h;

	cam_ray.x = ((2 * ((pix.x + 0.5) / scene->win_w)) - 1) * ratio * (tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.y = ((1 - (2 * ((pix.y + 0.5) / scene->win_h))) * tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.z = 1;
	cam_ray = rotat_zyx(cam_ray, ACTIVECAM.pitch, ACTIVECAM.yaw, 0);
	return(fast_normalize(cam_ray));
}

#endif
