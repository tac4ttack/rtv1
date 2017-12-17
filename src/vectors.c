#include "rtv1.h"

cl_float3			normalize_vect(cl_float3 v)
{
	cl_float3		res;
	cl_float		id;
    
    id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}