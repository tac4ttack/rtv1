#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx.h"

# ifdef MAC_KEYS
#  include "mac_keys.h"
# elif LINUX_KEYS
#  include "linux_keys.h"
# endif

# ifdef GPU
#  define MAX_SOURCE_SIZE	(0x100000)
#  define IS_GPU			1
# else
#  define IS_GPU			0
# endif

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# ifdef DEBUG
#  define DBUG					1
# else
#  define DBUG					0
# endif

# define DESTROYNOTIFY			17
# define KEYPRESSMASK			(1L<<0)
# define KEYRELEASEMASK			(1L<<1)
# define KEYPRESS				2
# define KEYRELEASE				3

# define DEG2RAD				(M_PI / 180)
# define RAD2DEG				(180 / M_PI)

# define WIDTH					e->param.win_w
# define HEIGHT					e->param.win_h
# define FOV					30
# define DEPTH					2000 //DAFUQ IS THIS SHIT?

# define NCAM					e->param.n_cams
# define NCON					e->param.n_cones
# define NCYL					e->param.n_cylinders
# define NLIG					e->param.n_lights
# define NPLA					e->param.n_planes
# define NSPH					e->param.n_spheres
# define ACTIVEOBJ				e->target_obj
# define CAM					e->cameras
# define CONES					e->cones
# define CYLIND					e->cylinders
# define LIGHT					e->lights
# define PLANE					e->planes
# define SPHERE					e->spheres
# define PARAM					e->param
# define ACTIVECAM				e->cameras[e->param.active_cam]

# define XML					e->xml
# define SCN					e->scene

typedef struct			s_fps
{
	struct timeval		step2;
	struct timeval		step;
	struct timeval		cur;
	float				delta_time;
	unsigned int		fps;
	unsigned int		ret_fps;
}						t_fps;

typedef struct			s_p2i
{
	int					x;
	int					y;
}						t_p2i;

typedef struct			s_hit
{
	float				dist;
	int					type;
	int					id;
	cl_float3			pos;
	cl_float3			normale;
}						t_hit;

typedef struct			s_cam
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float			fov;
	cl_float			pitch;
	cl_float			yaw;
	cl_float			roll;
}						t_cam;

typedef struct			s_cone
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float			angle;
	cl_int				color;
	cl_float3			diff;
	cl_float3			spec;
	cl_float			reflex;
}						t_cone;

typedef struct			s_cylinder
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			base_dir;
	cl_float			radius;
	cl_int				color;
	cl_float			height;
	cl_float3			diff;
	cl_float3			spec;
	cl_float			pitch;
	cl_float			yaw;
	cl_float			roll;
	cl_float			reflex;
}						t_cylinder;

typedef struct			s_light
{
	cl_int				type;
	cl_float3			pos;
	cl_float3			dir;
	cl_float			shrink;
	cl_float			brightness;
	cl_int				color;
}						t_light;

typedef struct			s_plane
{
	cl_float3			pos;
	cl_float3			normale;
	cl_int				color;
	cl_float3			diff;
	cl_float3			spec;
	cl_float			reflex;
}						t_plane;

typedef struct			s_sphere
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float			radius;
	cl_int				color;
	cl_float3			diff;
	cl_float3			spec;
	cl_float			reflex;
}						t_sphere;

typedef struct			s_param
{
	int					n_cams;
	int					n_cones;
	int					n_cylinders;
	int					n_lights;
	int					n_planes;
	int					n_spheres;
	int					active_cam;
	int					win_w;
	int					win_h;
	cl_float3			mvt;
	cl_float3			ambient;
	int					mou_x;
	int					mou_y;
	int					depth;
}						t_param;

typedef struct			s_node
{
	int					id;
	int					type;
	cl_float			fov;
	cl_float3			dir;
	cl_float3			pos;
	cl_float3			normale;
	cl_float			radius;
	cl_float			angle;
	cl_int				color;
	cl_int				light;
	cl_float			shrink;
	cl_float			brightness;
	cl_float			height;
	cl_float3			diff;
	cl_float3			spec;
	cl_float			reflex;
	struct s_node		*next;
}						t_node;

typedef	struct			s_xml
{
	char				*scene;
	int					scene_fd;
	char				**nodes;
	char				**sub_node;
	t_node				*node_lst;
	char				is_comm;
	char				in_scene;
	int					n_nodes;
	int					n_sub;
	int					lbra;
	int					rbra;
	int					slas;
	int					dquo;
	int					excl;
}						t_xml;

typedef struct			s_frame
{
	void				*ptr;
	char				*pix;
	int					x;
	int					y;
	int					w;
	int					h;
	int					row;
	int					bpp;
	int					endian;
}						t_frame;

typedef	struct			s_env
{
	void				*mlx;
	void				*win;
	t_frame				*frame;
	t_key				keys;
	int					win_w;
	int					win_h;
	int					sce_w;
	int					sce_h;
	int					cen_x;
	int					cen_y;
	int					debug;
	t_xml				*xml;
	char				*kernel_src;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	raytrace_queue;
	cl_program			program;
	cl_kernel			kernel_rt;
	cl_mem				frame_buffer;
	cl_mem				target_obj_buf;
	t_hit				target_obj;
	int					gpu;
	size_t				global;
	size_t				local;
	size_t				dif;
	unsigned int		count;
	t_param				param;
	t_cam				*cameras;
	cl_mem				cameras_mem;
	t_cone				*cones;
	cl_mem				cones_mem;
	t_cylinder			*cylinders;
	cl_mem				cylinders_mem;
	t_light				*lights;
	cl_mem				lights_mem;
	t_plane				*planes;
	cl_mem				planes_mem;
	t_sphere			*spheres;
	cl_mem				spheres_mem;
//	next data may be deleted after testing etc
	char				run;
	t_fps				fps;
}						t_env;

/*
*****		comment template		*****
*/

void					init(t_env *e, int ac, char *av);
void					set_hooks(t_env *e);

void					display_hud(t_env *e);

void					ui_cam(t_env *e);
void					ui_obj(t_env *e);
cl_float3				*get_target_pos(t_env *e);
cl_float3				*get_target_dir(t_env *e);

void					xml_allocate_cam(t_env *e);
void					xml_allocate_cone(t_env *e);
void					xml_allocate_cyl(t_env *e);
void					xml_allocate_light(t_env *e);
void					xml_allocate_plane(t_env *e);
void					xml_allocate_sphere(t_env *e);
int						xml_check_char(char c);
char					*xml_check_line(t_env *e, char *buf);
void					xml_data_angle(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_brightness(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_color(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_diffiouse(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_dir(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_height(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_normale(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_pos(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_radius(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_reflex(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_shrink(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_data_speculos(t_env *e, char **attributes, \
										int *i, t_node *node);										
void					xml_data_type(t_env *e, char **attributes, \
										int *i, t_node *node);
void					xml_init(t_env *e, int ac, char *av);
void					xml_get_file(t_env *e, int ac, char *av);
void					xml_list_add_first(t_node **begin, t_node *node);
void					xml_list_clean(t_env *e, t_node **list);
t_node					*xml_list_new(char type);
void					xml_node_clean(char **target);
void					xml_node_cam(t_env *e, char *node);
void					xml_node_cone(t_env *e, char *node);
void					xml_node_cylinder(t_env *e, char *node);
void					xml_node_light(t_env *e, char *node);
void					xml_node_plane(t_env *e, char *node);
void					xml_node_scene(t_env *e, char *node, char mod);
void					xml_node_sphere(t_env *e, char *node);
void					xml_parse_nodes(t_env *e);
void					xml_push_cam(t_env *e, t_node *list);
void					xml_push_cone(t_env *e, t_node *list);
void					xml_push_cyl(t_env *e, t_node *list);
void					xml_push_light(t_env *e, t_node *list);
void					xml_push_plane(t_env *e, t_node *list);
void					xml_push_sphere(t_env *e, t_node *list);

int						quit(t_env *e);
void					error(void);
void					s_error(char *str, t_env *e);
void					p_error(char *str, t_env *e);
void					print_usage();

int						mlx_img_pix_put(t_frame *sce, int x, int y, int color);
void					mlx_img_line(t_frame *sce, t_p2i p1, t_p2i p2, int c);
int						mlx_main_loop(t_env *e);
int						mlx_mouse_events(int btn, int x, int y, t_env *e);
void					mlx_keyboard_repeated(t_env *e);
int						mlx_key_release(int key, t_env *e);
int						mlx_key_press(int key, t_env *e);
int						mlx_key_simple(int key, t_env *e);

int						opencl_init(t_env *e, unsigned int count);
void					opencl_close(t_env *e);
int						opencl_allocate_scene_memory(t_env *e);
void					opencl_set_args(t_env *e);
int						draw(t_env *e);
void					refresh(t_env *e);
void					update_fps(t_fps *fps);

cl_float3				normalize_vect(cl_float3 v);
cl_float3				rotz(cl_float3 dir, float roll);
cl_float3				roty(cl_float3 dir, float yaw);
cl_float3				rotx(cl_float3 dir, float pitch);
cl_float3				rotcam(cl_float3 vect, float rad_pitch, float rad_yaw);
cl_float3				add_cl_float(cl_float3 v1, cl_float3 v2);
cl_float3				sub_cl_float(cl_float3 v1, cl_float3 v2);

#endif
