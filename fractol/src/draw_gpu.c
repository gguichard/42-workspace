/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gpu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 05:05:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 06:22:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <OpenCL/opencl.h>
#include "libft.h"
#include "opencl.h"
#include "fractol.h"

static char	*get_kernel_name(t_data *data)
{
	if (data->fract_fn == mandelbrot)
		return ("mandelbrot");
	else if (data->fract_fn == mandelbar)
		return ("mandelbar");
	else if (data->fract_fn == burning_ship)
		return ("burning_ship");
	else
		return ("julia");
}

static char	*read_sourcecode(void)
{
	int		fd;
	int		ret;
	char	*source;

	fd = open("src/kernel.cl", O_RDONLY);
	if (fd < 0)
		return (NULL);
	source = (char *)malloc(sizeof(char) * (4096 + 1));
	if (source == NULL)
		return (NULL);
	ret = read(fd, source, 4096);
	if (ret >= 0)
		source[ret] = '\0';
	else
		ft_strdel(&source);
	close(fd);
	return (source);
}

int			setup_opencl(t_data *data)
{
	t_cl	*cl;

	cl = &data->cl;
	cl->source = read_sourcecode();
	if (cl->source == NULL)
		return (0);
	cl->work_size = data->winsize.width * data->winsize.height;
	clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &cl->device, NULL);
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, NULL);
	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, NULL);
	cl->program = clCreateProgramWithSource(cl->context, 1
			, (const char **)&cl->source, NULL, NULL);
	clBuildProgram(cl->program, 0, NULL, NULL, NULL, NULL);
	cl->kernel = clCreateKernel(cl->program, get_kernel_name(data), NULL);
	cl->buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY
			, sizeof(int) * (data->winsize.width * data->winsize.height), NULL
			, NULL);
	data->use_opencl = 1;
	data->draw_fn = draw_gpu;
	return (1);
}

void		release_opencl(t_data *data)
{
	t_cl	*cl;

	cl = &data->cl;
	clReleaseKernel(cl->kernel);
	clReleaseMemObject(cl->buffer);
	clReleaseCommandQueue(cl->queue);
	clReleaseContext(cl->context);
	ft_strdel(&cl->source);
}

void		draw_gpu(t_data *data)
{
	t_cl	*cl;

	cl = &data->cl;
	clSetKernelArg(cl->kernel, 0, sizeof(cl->buffer), &cl->buffer);
	clSetKernelArg(cl->kernel, 1, sizeof(double), &(data->cam.x_min));
	clSetKernelArg(cl->kernel, 2, sizeof(double), &(data->cam.x_max));
	clSetKernelArg(cl->kernel, 3, sizeof(double), &(data->cam.y_min));
	clSetKernelArg(cl->kernel, 4, sizeof(double), &(data->cam.y_max));
	clSetKernelArg(cl->kernel, 5, sizeof(int), &(data->winsize.width));
	clSetKernelArg(cl->kernel, 6, sizeof(int), &(data->winsize.height));
	clSetKernelArg(cl->kernel, 7, sizeof(int), &(data->max_iters));
	clSetKernelArg(cl->kernel, 8, sizeof(double), &(data->motion.x));
	clSetKernelArg(cl->kernel, 9, sizeof(double), &(data->motion.y));
	clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL, &cl->work_size, NULL
			, 0, NULL, NULL);
	clEnqueueReadBuffer(cl->queue, cl->buffer, CL_FALSE, 0
			, sizeof(int) * (data->winsize.width * data->winsize.height)
			, data->lib.img_data, 0, NULL, NULL);
	clFinish(cl->queue);
}
