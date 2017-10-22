#define WINX 1920
#define WINY 1080

#define BACKCOLOR 0x00000000
#define SCOLOR 0x000000FF
#define PCOLOR 0x00FF0000
#define SSCOLOR 0x0000FF00
#define LCOLOR 0x00FFFFFF

#define DEG2RAD (M_PI / 180)
#define RAD2DEG (180 / M_PI)

#define CAM scene.cameras
#define CONES scene.cones
#define CYLIND scene.cylinders
#define LIGHT scene.lights
#define PLANE scene.planes
#define SPHERE scene.spheres
#define PARAM scene.param
#define ACTIVECAM scene.cameras[scene.param->active_cam]

#define OUTPUTE ((__global unsigned int *)output)[id]

tupedef struct			s_light_ray
{
	float3
}						t_light_ray;

typedef struct			s_hit
{
	float				dist;
	char				type;
	char				id;
	float3				pos;
	float3				normale;
}						t_hit;

typedef struct			s_cam
{
	float3				hor;
	float3				ver;
	float3				dir;
	float3				pos;
	float3				ray;
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
	float3				dir;
	int					color;
}						t_sphere;

typedef struct			s_param
{
	unsigned int		n_cams;
	unsigned int		n_cones;
	unsigned int		n_cylinders;
	unsigned int		n_lights;
	unsigned int		n_planes;
	unsigned int		n_spheres;
	unsigned int		active_cam;
}						t_param;

typedef struct			s_scene
{
	t_param				*param;
	t_cam				*cameras;
	t_cone				*cones;
	float				*cones_dst;
	t_cylinder			*cylinders;
	float				*cylinders_dst;
	t_light				*lights;
	float				*lights_dst;
	t_plane				*planes;
	float				*planes_dst;
	t_sphere			*spheres;
	float				*spheres_dst;
}						t_scene;
