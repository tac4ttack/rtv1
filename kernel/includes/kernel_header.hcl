#ifndef KERNEL_HEADER_HCL
# define KERNEL_HEADER_HCL

#define BACKCOLOR 0x00999999

#define MAX_DIST 10000000.0
#define SHADOW_BIAS 1000

#define CAM scene->cameras
#define CONES scene->cones
#define CYLIND scene->cylinders
#define LIGHT scene->lights
#define PLANE scene->planes
#define SPHERE scene->spheres
#define ACTIVECAM scene->cameras[scene->active_cam]

#define OUTPUT ((__global unsigned int *)output)[id]

#define OPTION_WAVE 	(1 << 1)
#define OPTION_SEPIA	(1 << 2)
#define OPTION_BW		(1 << 3)
//#define FLAG_DEBUG (1 << 2)

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
	int					shrink;
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

typedef	struct			s_tor
{
	float3				prim;
	unsigned int		hit_type;
	unsigned int		hit_id;
	unsigned int		color;
	char				check_g;
	char				check_d;
}						t_tor;

typedef struct			s_scene
{
	t_cam				__local *cameras;
	t_cone				__local *cones;
	t_cylinder			__local *cylinders;
	t_light				__local *lights;
	t_plane				__local *planes;
	t_sphere			__local *spheres;
	unsigned int		n_cams;
	unsigned int		n_cones;
	unsigned int		n_cylinders;
	unsigned int		n_lights;
	unsigned int		n_planes;
	unsigned int		n_spheres;
	unsigned int		active_cam;
	unsigned int		win_w;
	unsigned int		win_h;
	float3				ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
	float				u_time;
	int					flag;
	int					tor_count;
}						t_scene;

#endif
