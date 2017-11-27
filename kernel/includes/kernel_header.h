#define WINX 1920
#define WINY 1080

#define BACKCOLOR 0x00333333

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

typedef struct			s_light_ray
{
	float3				dir;
	float				dist;
}						t_light_ray;

typedef struct			s_hit
{
	float				dist;
	int					type;
	int					id;
	float3				pos;
	float3				normale;
}						t_hit;

typedef struct			s_cam
{
	float3				pos;
	float3				dir;
	float3				hor;
	float3				ver;
}						t_cam;

typedef struct			s_cone
{
	float3				pos;
	float3				dir;
	float				angle;
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
	int					type;
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
	float3				pos;
	float3				dir;
	float				radius;
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
	float				bloom;
	float3				mvt;
}						t_param;

typedef struct			s_scene
{
	t_param				*param;
	t_cam				__constant *cameras;
	t_cone				__constant *cones;
	float				*cones_dst;
	t_cylinder			__constant *cylinders;
	float				*cylinders_dst;
	t_light				__constant *lights;
	float				*lights_dst;
	t_plane				__constant *planes;
	float				*planes_dst;
	t_sphere			__constant *spheres;
	float				*spheres_dst;
	float3				ray;
}						t_scene;