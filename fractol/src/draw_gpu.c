/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gpu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 05:05:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/11 05:39:34 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <OpenCL/opencl.h>
#include "fractol.h"

static char	*read_sourcecode(void)
{
	int		fd;
	int		ret;
	char	*source;

	fd = open("src/kernel.cl", O_RDONLY);
	if (fd < 0)
		return (NULL);
	source = (char *)malloc(sizeof(char) * (2048 + 1));
	if (source == NULL)
		return (NULL);
	ret = read(fd, source, 2048);
	if (ret >= 0)
		source[ret] = '\0';
	close(fd);
	return (source);
}

void		draw_gpu(t_data *data)
{
	static const char	*source = NULL;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				buffer;
	size_t				work_size;

	if (source == NULL)
		source = read_sourcecode();
	clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
	queue = clCreateCommandQueue(context, device, 0, NULL);
	program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
	clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	kernel = clCreateKernel(program, "mandelbrot", NULL);
	buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY
			, sizeof(int) * (data->winsize.width * data->winsize.height)
			, NULL, NULL);
	clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
	clSetKernelArg(kernel, 1, sizeof(double), &(data->cam.x_min));
	clSetKernelArg(kernel, 2, sizeof(double), &(data->cam.x_max));
	clSetKernelArg(kernel, 3, sizeof(double), &(data->cam.y_min));
	clSetKernelArg(kernel, 4, sizeof(double), &(data->cam.y_max));
	clSetKernelArg(kernel, 5, sizeof(int), &(data->winsize.width));
	clSetKernelArg(kernel, 6, sizeof(int), &(data->winsize.height));
	clSetKernelArg(kernel, 7, sizeof(int), &(data->max_iters));
	work_size = data->winsize.width * data->winsize.height;
	clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &work_size, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(queue, buffer, CL_FALSE, 0
			, sizeof(int) * (data->winsize.width * data->winsize.height)
			, data->lib.img_data, 0, NULL, NULL);
	clFinish(queue);
}
