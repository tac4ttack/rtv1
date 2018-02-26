#include "rtv1.h"

void		opencl_set_args(t_env *e)
{
	e->err = 0;
	e->err = clSetKernelArg(e->kernel_rt, 0, sizeof(cl_mem), &e->frame_buffer);
	e->err |= clSetKernelArg(e->kernel_rt, 1, sizeof(cl_mem), &e->target_obj_buf);
	e->err |= clSetKernelArg(e->kernel_rt, 2, sizeof(cl_mem), &e->scene_mem);
	e->err |= clSetKernelArg(e->kernel_rt, 3, sizeof(cl_mem), &e->cameras_mem);
	e->err |= clSetKernelArg(e->kernel_rt, 4, sizeof(cl_mem), &e->cones_mem);
	e->err |= clSetKernelArg(e->kernel_rt, 5, sizeof(cl_mem), &e->cylinders_mem);
	e->err |= clSetKernelArg(e->kernel_rt, 6, sizeof(cl_mem), &e->lights_mem);
	e->err |= clSetKernelArg(e->kernel_rt, 7, sizeof(cl_mem), &e->planes_mem);
	e->err |= clSetKernelArg(e->kernel_rt, 8, sizeof(cl_mem), &e->spheres_mem);
	e->err |= clSetKernelArg(e->kernel_rt, 9, sizeof(t_scene), NULL);
	e->err |= clSetKernelArg(e->kernel_rt, 10, sizeof(t_cam) * NCAM + 4, NULL);
	e->err |= clSetKernelArg(e->kernel_rt, 11, sizeof(t_cone) * NCON + 4, NULL);
	e->err |= clSetKernelArg(e->kernel_rt, 12, sizeof(t_cylinder) * NCYL + 4, NULL);
	e->err |= clSetKernelArg(e->kernel_rt, 13, sizeof(t_light) * NLIG + 4, NULL);
	e->err |= clSetKernelArg(e->kernel_rt, 14, sizeof(t_plane) * NPLA + 4, NULL);
	e->err |= clSetKernelArg(e->kernel_rt, 15, sizeof(t_sphere) * NSPH + 4, NULL);
	e->err |= clSetKernelArg(e->kernel_rt, 16, sizeof(float), &(e->fps.u_time));
//	e->err |= clSetKernelArg(e->kernel_rt, 17, \
//								sizeof(t_tor) * e->node_count , e->tree);
	if (e->err != CL_SUCCESS)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to send arguments to kernel!", e);
	}
}

int			get_imgptr(t_env *e)
{
	clFinish(e->raytrace_queue);
	 // the "CL_TRUE" flag blocks the read operation until all work items have finished their computation
	e->err = clEnqueueReadBuffer(e->raytrace_queue, e->frame_buffer, CL_TRUE, 0, \
			(e->count * 4), e->frame->pix, 0, NULL, NULL);
	if (e->run == 1)
	{
		e->err = clEnqueueReadBuffer(e->raytrace_queue, e->target_obj_buf, \
		CL_FALSE, 0, sizeof(t_hit), &e->target_obj, 0, NULL, NULL);
		e->run = 0;
	}
	if (e->err != CL_SUCCESS)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to read output array!", e);
	}
	return (0);
}

int			draw(t_env *e)
{
	const size_t	g[2] = {WIDTH, HEIGHT};

	opencl_set_args(e);
	e->err = clGetKernelWorkGroupInfo(e->kernel_rt, e->device_id, \
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(e->local), &e->local, NULL); // useless avec le tableau G?
	if (e->err != CL_SUCCESS)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to retrieve kernel work group info!", e);
	}
	e->err = clEnqueueNDRangeKernel(e->raytrace_queue, e->kernel_rt, 2, NULL, \
			g, NULL, 0, NULL, NULL);
	if (e->err)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to execute kernel!\n", e);
	}
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
