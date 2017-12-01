#include "rtv1.h"

void		opencl_set_args(t_env *e)
{
	int		err;

	err = 0;
	err = clSetKernelArg(e->kernel, 0, sizeof(cl_mem), &e->output);
	err |= clSetKernelArg(e->kernel, 1, sizeof(t_param), &e->param);
	err |= clSetKernelArg(e->kernel, 2, sizeof(cl_mem), &e->cameras_mem);
	err |= clSetKernelArg(e->kernel, 3, sizeof(cl_mem), &e->cones_mem);
	err |= clSetKernelArg(e->kernel, 4, sizeof(cl_mem), &e->cylinders_mem);
	err |= clSetKernelArg(e->kernel, 5, sizeof(cl_mem), &e->lights_mem);
	err |= clSetKernelArg(e->kernel, 6, sizeof(cl_mem), &e->planes_mem);
	err |= clSetKernelArg(e->kernel, 7, sizeof(cl_mem), &e->spheres_mem);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to send arguments to kernel!", e);
	}
}

int			get_imgptr(t_env *e)
{
	int		err;

	clFinish(e->commands);
	 // the "CL_TRUE" flag blocks the read operation until all work items have finished their computation
	err = clEnqueueReadBuffer(e->commands, e->output, CL_TRUE, 0, \
			sizeof(char) * (e->count * 4), e->frame->pix, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to read output array!", e);
	}
	return (0);
}

int			draw(t_env *e)
{
	int		err;
	const size_t	g[2] = {WIDTH, HEIGHT};

	opencl_set_args(e);
	err = clGetKernelWorkGroupInfo(e->kernel, e->device_id, \
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(e->local), &e->local, NULL);
//	e->local = 1024 | e->count = 2073600
//	CL_KERNEL_WORK_GROUP_SIZE = 4528
//	printf("CL_KERNEL_WORK_GROUP_SIZE = %d\n", CL_KERNEL_WORK_GROUP_SIZE);
//	printf("e->local = %zu | e->count = %u\n", e->local, e->count);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to retrieve kernel work group info!", e);
	}
	e->global = (size_t)e->count;
	//e->local = 256;
	err = clEnqueueNDRangeKernel(e->commands, e->kernel, 2, NULL, \
			g, NULL, 0, NULL, NULL);
	if (err)
		s_error("Error: Failed to execute kernel!\n", e);
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
