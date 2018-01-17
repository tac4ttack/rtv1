#include "rtv1.h"

t_scene			grab_data(t_cam *cameras, \
						  t_cone *cones, \
						  t_cylinder *cylinders, \
						  t_light *lights, \
						  t_plane *planes, \
						  t_sphere *spheres, \
						  t_param param)
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