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