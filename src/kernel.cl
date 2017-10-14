__kernel void ray_trace(__global char *output)
{
	float3	cam_origin;
	float3	boule_origin;
	float	radius = 42;
	float3	view_planeup;
	float	view_planedist = 1.0;
	float	view_planeh = 0.5;
	float	view_planew = 0.35;

	boule_origin[0] = 666;
	boule_origin[1] = 666;
	boule_origin[2] = 2100;
	cam_origin[0] = 1920 / 2;
	cam_origin[1] = 1080 / 2;
	cam_origin[2] = 2000 / 2;
	view_planeup = cam_origin + ((vec_dir * view_planedist) + \
		(upVec * (view_planeh / 2.0))) - (rightVec * veiw_planew / 2.0);
}
