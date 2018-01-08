#include "rtv1.h"

cl_float3			normalize_vect(cl_float3 v)
{
	cl_float3		res;
	cl_float		id;
    
    id = 1 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	res.x = v.x * id;
	res.y = v.y * id;
	res.z = v.z * id;
	return (res);
}

cl_float3			add_cl_float(cl_float3 v1, cl_float3 v2)
{
	cl_float3		res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

cl_float3			sub_cl_float(cl_float3 v1, cl_float3 v2)
{
	cl_float3		res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

void				kernel_refresh(t_env *e, char *str)
{
	int				err;

	if (!(e->kernel = clCreateKernel(e->program, str, &err)) \
		|| err != CL_SUCCESS)
		{
			ft_putendl("Error: Failed to create compute kernel!\n");
			return;
		}
	opencl_set_args(e);
}

void				set_mouseargs(t_env *e)
{
	int				err;

	err = 0;
	err = clSetKernelArg(e->kernel, 8, sizeof(int), &e->mou_x);
	err |= clSetKernelArg(e->kernel, 9, sizeof(int), &e->mou_y);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to send arguments to kernel!", e);
	}
}

void				get_activeobj(t_env *e)
{
	int				err;
	const size_t	g = 1;

	mlx_mouse_get_pos(e->win, &e->mou_x, &e->mou_y);
	kernel_refresh(e, "hit_activeobj");
	set_mouseargs(e);
	err = clEnqueueNDRangeKernel(e->commands, e->kernel, 1, NULL, \
			&g, NULL, 0, NULL, NULL);
	clFinish(e->commands);
	err = clEnqueueReadBuffer(e->commands, e->output, CL_TRUE, 0, \
			sizeof(t_hit), &e->param.target_obj, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to read output array!", e);
	}
	printf("type : %d, id ; %d, x : %d, y : %d\n", e->param.target_obj.type, e->param.target_obj.id, e->mou_x, e->mou_y);
	kernel_refresh(e, "ray_trace");
}

