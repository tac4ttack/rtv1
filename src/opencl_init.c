#include "rtv1.h"

int			opencl_builderrors(t_env *e, int err)
{
	size_t	len;
	char	buffer[50000];

	if (err == 1)
		ft_putendl("Error: Failed to create device group!");
	else if (err == 2)
		ft_putendl("Error: Failed to create compute context!");
	else if (err == 3)
		ft_putendl("Error: Failed to create commands queue!");
	else if (err == 4)
		ft_putendl("Error: Failed to create compute program!");
	else if (err == 5)
	{
		ft_putendl("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(e->program, e->device_id, \
				CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		ft_putendl(buffer);
	}
	else if (err == 6)
		ft_putendl("Error: Failed to create compute kernel!\n");
	else if (err == 7)
		ft_putendl("Error: Failed to allocate device memory!\n");
	if (err >= 5)
		exit(1);
	return (EXIT_FAILURE);
}

int			opencl_allocate_scene_memory(t_env *e)
{

	if (NCAM > 0)
		if (!(e->cameras_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_cam) * NCAM, e->cameras, NULL)))
			return (opencl_builderrors(e, 7));
	if (NCON > 0)
		if (!(e->cones_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_cone) * NCON, e->cones, NULL)))
			return (opencl_builderrors(e, 7));
	if (NCYL > 0)
		if (!(e->cylinders_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_cylinder) * NCYL, e->cylinders, NULL)))
			return (opencl_builderrors(e, 7));
	if (NLIG > 0)
		if (!(e->lights_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_light) * NLIG, e->lights, NULL)))
			return (opencl_builderrors(e, 7));
	if (NPLA > 0)
		if (!(e->planes_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_plane) * NPLA, e->planes, NULL)))
			return (opencl_builderrors(e, 7));
	if (NSPH > 0)
		if (!(e->spheres_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_sphere) * NSPH, e->spheres, NULL)))
			return (opencl_builderrors(e, 7));
	return (0);
}

int			opencl_build(t_env *e, unsigned int count)
{
	int		err;

	if ((err = clBuildProgram(e->program, 0, NULL, "-I ./kernel/includes/", \
				NULL, NULL)) != CL_SUCCESS)
		return (opencl_builderrors(e, 5));
	if (!(e->kernel_raytrace = clCreateKernel(e->program, "ray_trace", &err)) \
		|| err != CL_SUCCESS)
		return (opencl_builderrors(e, 6));
	if (!(e->kernel_activeobj = clCreateKernel(e->program, "hit_activeobj", &err)) \
		|| err != CL_SUCCESS)
		return (opencl_builderrors(e, 6));
	if (!(e->output_ptr = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY, \
		count, NULL, NULL)))
		return (opencl_builderrors(e, 7));
	if (!(e->output_obj = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY, \
		sizeof(t_hit), NULL, NULL)))
		return (opencl_builderrors(e, 7));
	opencl_allocate_scene_memory(e);
	return (0);
}

void		load_kernel(t_env *e)
{
	int		fd;
	int		ret;
	char	*line;

	if ((e->kernel_src = ft_strdup("#define FROM_KERNEL\n")) == NULL)
	{
		s_error("Error during allocating memory for kernel source code", e);
		exit(1);
	}
	if ((fd = open("./kernel/kernel.cl", O_RDONLY)) < 0)
		s_error("Error opening kernel", e);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		e->kernel_src = ft_strjoin_frs1(e->kernel_src, "\n");
		e->kernel_src = ft_strjoin_free(e->kernel_src, line);
	}
	(ret == -1 ? s_error("GNL read error", e) : 0);
	e->kernel_src = ft_strjoin_frs1(e->kernel_src, "\n");
	close(fd);
}

int			opencl_init(t_env *e, unsigned int count)
{
	int		err;

	load_kernel(e);
	if ((err = clGetDeviceIDs(NULL, e->gpu ? CL_DEVICE_TYPE_GPU : \
				CL_DEVICE_TYPE_CPU, 1, &e->device_id, NULL)) != CL_SUCCESS)
		return (opencl_builderrors(e, 1));
	if (!(e->context = clCreateContext(0, 1, &e->device_id, \
				NULL, NULL, &err)))
		return (opencl_builderrors(e, 2));
	if (!(e->commands_raytrace = clCreateCommandQueue(e->context, \
				e->device_id, 0, &err)))
		return (opencl_builderrors(e, 3));
	if (!(e->commands_activeobj = clCreateCommandQueue(e->context, \
				e->device_id, 0, &err)))
		return (opencl_builderrors(e, 3));
	if (!(e->program = clCreateProgramWithSource(e->context, 1, \
				(const char **)&e->kernel_src, NULL, &err)))
		return (opencl_builderrors(e, 4));
	opencl_build(e, count);
	return (0);
}
