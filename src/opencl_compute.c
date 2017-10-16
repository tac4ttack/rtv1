#include "rtv1.h"

void		opencl_set_args(t_env *e)
{
	int		err;

	err = 0;
	e->test.x = 1;
	e->test.y = 2;
	e->test.z = 3;
	err = clSetKernelArg(e->kernel, 0, sizeof(cl_mem), &e->output);
//	err |= clSetKernelArg(e->kernel, 1, sizeof(t_env), &e);
//	err |= clSetKernelArg(e->kernel, 1, sizeof(int), &e->win_w);
//	err |= clSetKernelArg(e->kernel, 2, sizeof(int), &e->win_h);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to send arguments to kernel!");
//		ft_putstr("Error: Failed to set kernel arguments!");
//		ft_putnbr(err);
//		ft_putchar('\n');
//		exit(1);
	}
}

int			get_imgptr(t_env *e)
{
	int		err;

	clFinish(e->commands);
	err = clEnqueueReadBuffer(e->commands, e->output, CL_TRUE, 0, \
			sizeof(char) * (e->count * 4), e->scene->pix, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putnbr(err);
		ft_putchar('\n');
		s_error("Error: Failed to read output array!");
//		ft_putstr("Error: Failed to read output array!");
//		ft_putnbr(err);
//		ft_putchar('\n');
//		exit(1);
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
