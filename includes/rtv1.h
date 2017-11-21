#ifndef RTV1_H
# define RTV1_H

# ifdef MAC_KEYS
#  include "mac_keys.h"
# elif LINUX_KEYS
#  include "linux_keys.h"
# endif

# ifdef GPU
#  define MAX_SOURCE_SIZE	(0x100000)
#  define IS_GPU			1
#  ifdef __APPLE__
#   include <OpenCL/opencl.h>
#  else
#   include <CL/cl.h>
#  endif
# endif

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

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

# define WIDTH					1920
# define HEIGHT					1080
# define DEPTH					2000

# define NCAM					e->param.n_cams
# define NCON					e->param.n_cones
# define NCYL					e->param.n_cylinders
# define NLIG					e->param.n_lights
# define NPLA					e->param.n_planes
# define NSPH					e->param.n_spheres

# define XML					e->xml
# define SCN					e->scene

typedef struct			s_p2i
{
	int					x;
	int					y;
}						t_p2i;

typedef struct			s_cam
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			hor;
	cl_float3			ver;
//	cl_float3			ray;   DAFUQ IS THIS SHIT?
}						t_cam;

typedef struct			s_cone
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float			angle;
	cl_int				color;
}						t_cone;

typedef struct			s_cylinder
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float			radius;
	cl_int				color;
}						t_cylinder;

typedef struct			s_light
{
	cl_char				type;
	cl_float3			pos;
	cl_float3			dir;
	cl_float			intensity;
	cl_int				color;
}						t_light;

typedef struct			s_plane
{
	cl_float3			pos;
	cl_float3			normale;
	cl_int				color;
}						t_plane;

typedef struct			s_sphere
{
	cl_float3			pos;
	cl_float3			dir;
	cl_float			radius;
	cl_int				color;
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
	cl_float			bloom;
	cl_float3			mvt;
}						t_param;

typedef struct			s_node
{
	int					id;
	char				type;
	cl_float3			hor;
	cl_float3			ver;
	cl_float3			dir;
	cl_float3			pos;
	cl_float3			normale;
	cl_float			radius;
	cl_float			angle;
	cl_int				color;
	cl_float			intensity;
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
	int					mou_x;
	int					mou_y;
	int					debug;
	t_xml				*xml;
	char				*kernel_src;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				output;
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
	cl_float3			mvt;
//	next data may be deleted after testing etc
	char				run;
}						t_env;

/*
*****		comment template		*****
*/

void					init(t_env *e, int ac, char *av);
void					set_hooks(t_env *e);

void					xml_init(t_env *e, int ac, char *av);
void					xml_get_file(t_env *e, int ac, char *av);
int						xml_check_char(char c);
char					*xml_check_line(t_env *e, char *buf);
void					xml_parse_nodes(t_env *e);
char					**xml_split_nodes(t_env *e, char *scene);
void					xml_node_clean(char **target);
t_node					*xml_list_new(char type);
void					xml_list_add_first(t_node **begin, t_node *node);
void					xml_node_cam(t_env *e, char *node);
void					xml_node_cone(t_env *e, char *node);
void					xml_node_cylinder(t_env *e, char *node);
void					xml_node_light(t_env *e, char *node);
void					xml_node_plane(t_env *e, char *node);
void					xml_node_sphere(t_env *e, char *node);

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

int						opencl_init(t_env *e);
void					opencl_close(t_env *e);
int						opencl_allocate_scene_memory(t_env *e);
int						draw(t_env *e);
void					refresh(t_env *e);

#endif
