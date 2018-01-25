#include "rtv1.h"

void		opencl_set_args(t_env *e)
{
	int		err;

	err = 0;
	err = clSetKernelArg(e->kernel_rt, 0, sizeof(cl_mem), &e->frame_buffer);
	err |= clSetKernelArg(e->kernel_rt, 1, sizeof(t_param), &e->param);
	err |= clSetKernelArg(e->kernel_rt, 2, sizeof(cl_mem), &e->cameras_mem);
	err |= clSetKernelArg(e->kernel_rt, 3, sizeof(cl_mem), &e->cones_mem);
	err |= clSetKernelArg(e->kernel_rt, 4, sizeof(cl_mem), &e->cylinders_mem);
	err |= clSetKernelArg(e->kernel_rt, 5, sizeof(cl_mem), &e->lights_mem);
	err |= clSetKernelArg(e->kernel_rt, 6, sizeof(cl_mem), &e->planes_mem);
	err |= clSetKernelArg(e->kernel_rt, 7, sizeof(cl_mem), &e->spheres_mem);
	err |= clSetKernelArg(e->kernel_rt, 8, sizeof(cl_mem), &e->target_obj_buf);
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

	clFinish(e->raytrace_queue);
	 // the "CL_TRUE" flag blocks the read operation until all work items have finished their computation
	err = clEnqueueReadBuffer(e->raytrace_queue, e->frame_buffer, CL_TRUE, 0, \
			(e->count * 4), e->frame->pix, 0, NULL, NULL);
	if (e->run == 1)
	{
		err = clEnqueueReadBuffer(e->raytrace_queue, e->target_obj_buf, \
		CL_FALSE, 0, sizeof(t_hit), &e->target_obj, 0, NULL, NULL);
		e->run = 0;
	}
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
	err = clGetKernelWorkGroupInfo(e->kernel_rt, e->device_id, \
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(e->local), &e->local, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to retrieve kernel work group info!", e);
	}
	err = clEnqueueNDRangeKernel(e->raytrace_queue, e->kernel_rt, 2, NULL, \
			g, NULL, 0, NULL, NULL);
	if (err)
		s_error("Error: Failed to execute kernel!\n", e);
	get_imgptr(e);
	return (0);
}

void		opencl_close(t_env *e)
{
	clReleaseMemObject(e->frame_buffer);
	clReleaseMemObject(e->target_obj_buf);
	clReleaseProgram(e->program);
	clReleaseKernel(e->kernel_rt);
	clReleaseCommandQueue(e->raytrace_queue);
	clReleaseContext(e->context);
}
