#include "rtv1.h"

cl_float3           rotx(cl_float3 dir, float pitch) // dir doit être normalisé, pitch en radians
{
    cl_float3       newdir;

    newdir.x = dir.x;
    newdir.y = dir.y * cos(pitch) + dir.z * -sin(pitch);
    newdir.z = dir.y * sin(pitch) + dir.z * cos(pitch);
    return (normalize_vect(newdir));
}

cl_float3           roty(cl_float3 dir, float yaw) // dir doit être normalisé, yaw en radians
{
    cl_float3       newdir;

    newdir.x = dir.x * cos(yaw) + dir.z * sin(yaw);
    newdir.y = dir.y;
    newdir.z = dir.x * -sin(yaw) + dir.z * cos(yaw);
    return (normalize_vect(newdir));
}

cl_float3           rotz(cl_float3 dir, float roll) // dir doit être normalisé, roll en radians
{
    cl_float3       newdir;

    newdir.x = dir.x * cos(roll) + dir.y * -sin(roll);
    newdir.y = dir.x * sin(roll) + dir.y * cos(roll);
    newdir.z = dir.z;
    return (normalize_vect(newdir));
}

cl_float3           rotcam(cl_float3 vect, float rad_pitch, float rad_yaw)
{
	cl_float3			res;
	float			rad_roll;

	rad_roll = 0;
	res.x = vect.x * cos(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_pitch) \
            * -sin(rad_roll) + cos(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) \
            + vect.z  * (-sin(rad_roll) * -sin(rad_pitch) + cos(rad_roll) \
            * sin(rad_yaw) * cos(rad_pitch));
	res.y = vect.x * sin(rad_roll) * cos(rad_yaw) + vect.y * (cos(rad_roll) \
            * cos(rad_pitch) + sin(rad_roll) * sin(rad_yaw) * sin(rad_pitch)) \
            + vect.z * (cos(rad_roll) * -sin(rad_pitch) + sin(rad_roll) \
            * sin(rad_yaw) * cos(rad_pitch));
	res.z = vect.x * -sin(rad_yaw) + vect.y * cos(rad_yaw) * sin(rad_pitch) \
            + vect.z * cos(rad_yaw) * cos(rad_pitch);
	return (normalize_vect(res));
}
