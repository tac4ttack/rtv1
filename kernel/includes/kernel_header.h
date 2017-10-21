#define WINX 1920
#define WINY 1080
#define BACKCOLOR 0x00000000
#define SCOLOR 0x000000FF
#define PCOLOR 0x00FF0000
#define SSCOLOR 0x0000FF00
#define LCOLOR 0x00FFFFFF
#define DEG2RAD (M_PI / 180)
#define RAD2DEG (180 / M_PI)
#define OUTPUTE ((__global unsigned int *)output)[id]

typedef struct			s_cam
{
	float3				hor;
	float3				ver;
	float3				dir;
	float3				pos;
}						t_cam;

typedef struct			s_cone
{
	float3				pos;
	float3				dir;
	int					color;
}						t_cone;

typedef struct			s_cylinder
{
	float3				pos;
	float3				dir;
	float				radius;
	int					color;
}						t_cylinder;

typedef struct			s_light
{
	char				type;
	float3				pos;
	float3				dir;
	float				intensity;
	int					color;
}						t_light;

typedef struct			s_plane
{
	float3				pos;
	float3				normale;
	int					color;
}						t_plane;

typedef struct			s_sphere
{
	float				radius;
	float3				pos;
//	float3				dir;
	int					color;
}						t_sphere;

typedef struct			s_object
{
	char				type;
	char				id;
	t_cam				cam;
	t_cone				cone;
	t_cylinder			cylinder;
	t_light				light;
	t_plane				plane;
	t_sphere			sphere;
}						t_object;

float3			sub_vect(float3 v1, float3 v2)
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
}

float3			mult_fvect(float m, float3 v)
{
	float3		res;

	res.x = m * v.x;
	res.y = m * v.y;
	res.z = m * v.z;
	return (res);
}

float			modh_vect(int x)
{
	return ((float)((float)x - (WINX / 2.0)) / (WINX / 2.0));
}

float			modv_vect(int y)
{
	return ((float)(((float)y - (WINY / 2.0)) / (WINY / 2.0) * WINY / WINX));
}
