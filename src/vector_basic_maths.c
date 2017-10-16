#include "rtv1.h"

t_v3f		v3f_add(t_v3f v1, t_v3f v2)
{
	t_v3f	res;

	res.x = v1.x + v2.x;
	res.y = v1.x + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_v3f		v3f_sub(t_v3f v1, t_v3f v2)
{
	t_v3f	res;

	res.x = v1.x - v2.x;
	res.y = v1.x - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_v3f		v3f_mul(float a, t_v3f vec)
{
	t_v3f	res;

	res.x = vec.x * a;
	res.y = vec.y * a;
	res.z = vec.z * a;
	return (res);
}

float		v3f_norm(t_v3f vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}
