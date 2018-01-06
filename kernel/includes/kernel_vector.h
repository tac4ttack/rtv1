/*float3			sub_vect(float3 v1, float3 v2)
{
	float3		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

float3			add_vect(float3 v1, float3 v2)
{
	float3		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

float			norme_vect(float3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float3			normalize_vect(float3 v)
{
	float3		res;
	int			id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}

float			dot_vect(float3 v1, float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
} */

float3			mult_fvect(float m, float3 v)
{
	float3		res;

	res.x = m * v.x;
	res.y = m * v.y;
	res.z = m * v.z;
	return (res);
}

float			modh_vect(int x, int win_w)
{
	return ((float)((float)x - (win_w / 2.0)) / (win_w / 2.0));
}

float			modv_vect(int y, int win_h, int win_w)
{
	return ((float)(((float)y - (win_h / 2.0)) / (win_h / 2.0) * win_h / win_w));
}
