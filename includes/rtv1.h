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
# include "get_next_line.h"

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

typedef struct			s_p2i
{
	int					x;
	int					y;
}						t_p2i;

typedef struct			s_v3f
{
	float				x;
	float				y;
	float				z;
}						t_v3f;

typedef struct			s_ray
{
	t_v3f				ori;
	t_v3f				dir;
	float				t;
}						t_ray;

typedef struct			s_sphere
{
	t_v3f				center;
	float				radius;
	int					hue;
}						t_sphere;

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
	t_frame				*scene;
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
//	next data can be deleted after testing etc
	cl_float3			test;
	char				run;
	float				mvx;
	float				mvy;
	float				mvz;
}						t_env;

/*
*****		comment template		*****
*/

void					init(t_env *e);

int						quit(t_env *e);
void					error(void);
void					s_error(char *str);

int						mlx_img_pix_put(t_frame *sce, int x, int y, int color);
void					mlx_img_line(t_frame *sce, t_p2i p1, t_p2i p2, int c);
int						mlx_main_loop(t_env *e);
int						mlx_mouse_events(int btn, int x, int y, t_env *e);
void					mlx_keyboard_repeated(t_env *e);
int						mlx_key_release(int key, t_env *e);
int						mlx_key_press(int key, t_env *e);
int						mlx_key_simple(int key, t_env *e);

int						opencl_init(t_env *e);
int						draw(t_env *e);
void					refresh(t_env *e);

t_v3f					v3f_add(t_v3f v1, t_v3f v2);
t_v3f					v3f_sub(t_v3f v1, t_v3f v2);
t_v3f					v3f_mul(float a, t_v3f vec);
float					v3f_norm(t_v3f vec);
t_v3f					v3f_c_prod(t_v3f v1, t_v3f v2);
float					v3f_d_prod(t_v3f v1, t_v3f v2);

#endif
