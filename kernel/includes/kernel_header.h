#define WINX 1920
#define WINY 1080
#define BACKCOLOR 0x00000000
#define SCOLOR 0x000000FF
#define PCOLOR 0x00FF0000
#define SSCOLOR 0x0000FF00
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
	t_cam				cam;
	t_cone				cone;
	t_cylinder			cylinder;
	t_light				light;
	t_plane				plane;
	t_sphere			sphere;
}						t_object;
