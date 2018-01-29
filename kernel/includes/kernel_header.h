#define BACKCOLOR 0x00999999

#define MAX_DIST 10000000.0 // epsilon 0.00000001 ?

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
	float				fov;
	float				pitch;
	float				yaw;
	float				roll;
}						t_cam;

typedef struct			s_cone
{
	float3				pos;
	float3				dir;
	float				angle;
	int					color;
	float3				diff;
	float3				spec;
	float				reflex;
}						t_cone;

typedef struct			s_cylinder
{
	float3				pos;
	float3				dir;
	float3				base_dir;
	float				radius;
	int					color;
	float				height;
	float3				diff;
	float3				spec;
	float				pitch;
	float				yaw;
	float				roll;
	float				reflex;
}						t_cylinder;

typedef struct			s_light
{
	int					type;
	float3				pos;
	float3				dir;
	float				intensity;
	float				brightness;
	int					color;
}						t_light;

typedef struct			s_plane
{
	float3				pos;
	float3				normale;
	int					color;
	float3				diff;
	float3				spec;
	float				reflex;
}						t_plane;

typedef struct			s_sphere
{
	float3				pos;
	float3				dir;
	float				radius;
	int					color;
	float3				diff;
	float3				spec;
	float				reflex;
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
	unsigned int		win_w;
	unsigned int		win_h;
	float3				mvt;
	float3				ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
}						t_param;

typedef struct			s_scene
{
	t_param				*param;
	t_cam				__constant *cameras;
	t_cone				__constant *cones;
	t_cylinder			__constant *cylinders;
	t_light				__constant *lights;
	t_plane				__constant *planes;
	t_sphere			__constant *spheres;
	float3				ray;
	int2				pix;
}						t_scene;
