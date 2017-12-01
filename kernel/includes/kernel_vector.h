double3			sub_vect(double3 v1, double3 v2)
{
	double3		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

double3			add_vect(double3 v1, double3 v2)
{
	double3		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

double			norme_vect(double3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double3			normalize_vect(double3 v)
{
	double3		res;
	int			id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}

double			dot_vect(double3 v1, double3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double3			mult_fvect(double m, double3 v)
{
	double3		res;

	res.x = m * v.x;
	res.y = m * v.y;
	res.z = m * v.z;
	return (res);
}

double			modh_vect(int x)
{
	return ((double)((double)x - (WINX / 2.0)) / (WINX / 2.0));
}

double			modv_vect(int y)
{
	return ((double)(((double)y - (WINY / 2.0)) / (WINY / 2.0) * WINY / WINX));
}
