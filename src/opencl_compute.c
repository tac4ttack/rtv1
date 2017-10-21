#include "rtv1.h"

void		opencl_set_args(t_env *e)
{
	int		err;

	err = 0;
	err = clSetKernelArg(e->kernel, 0, sizeof(cl_mem), &e->output);
	err |= clSetKernelArg(e->kernel, 1, sizeof(cl_float3), &e->mvt);
	err |= clSetKernelArg(e->kernel, 2, sizeof(t_scene), &e->scene);
	err |= clSetKernelArg(e->kernel, 3, sizeof(cl_mem), &e->cameras_mem);
	err |= clSetKernelArg(e->kernel, 4, sizeof(cl_mem), &e->cones_mem);
	err |= clSetKernelArg(e->kernel, 5, sizeof(cl_mem), &e->cylinders_mem);
	err |= clSetKernelArg(e->kernel, 6, sizeof(cl_mem), &e->lights_mem);
	err |= clSetKernelArg(e->kernel, 7, sizeof(cl_mem), &e->planes_mem);
	err |= clSetKernelArg(e->kernel, 8, sizeof(cl_mem), &e->spheres_mem);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to send arguments to kernel!");
	}
}

int			get_imgptr(t_env *e)
{
	int		err;

	clFinish(e->commands);
	err = clEnqueueReadBuffer(e->commands, e->output, CL_TRUE, 0, \
			sizeof(char) * (e->count * 4), e->frame->pix, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to read output array!");
	}
	return (0);
}

int			draw(t_env *e)
{
	int		err;

	opencl_set_args(e);
	err = clGetKernelWorkGroupInfo(e->kernel, e->device_id, \
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(e->local), &e->local, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to retrieve kernel work group info!");
	}
	e->global = (size_t)e->count;
	err = clEnqueueNDRangeKernel(e->commands, e->kernel, 1, NULL, \
			&e->global, &e->local, 0, NULL, NULL);
	if (err)
		s_error("Error: Failed to execute kernel!\n");
	get_imgptr(e);
	return (0);
}

void		opencl_close(t_env *e)
{
	clReleaseMemObject(e->output);
	clReleaseProgram(e->program);
	clReleaseKernel(e->kernel);
	clReleaseCommandQueue(e->commands);
	clReleaseContext(e->context);
}
