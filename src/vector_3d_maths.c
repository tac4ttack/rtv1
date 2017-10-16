#include "rtv1.h"

float		v3f_d_prod(t_v3f v1, t_v3f v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_v3f		v3f_c_prod(t_v3f v1, t_v3f v2)
{
	t_v3f	res;

	res.x = (v1.y * v2.z) - (v1.z * v2.y);
	res.y = (v1.z * v2.x) - (v1.x * v2.z );
	res.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (res);
}
