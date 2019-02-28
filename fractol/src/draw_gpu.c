/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gpu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 05:05:30 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 09:54:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <OpenCL/opencl.h>
#include "libft.h"
#include "opencl.h"
#include "fractol.h"

static int	get_fract_type(t_data *data)
{
	if (data->fract_fn == mandelbrot)
		return (1);
	else if (data->fract_fn == mandelbar)
		return (2);
	else if (data->fract_fn == burning_ship)
		return (3);
	else
		return (0);
}

static char	*read_sourcecode(void)
{
	int		fd;
	int		ret;
	char	*source;

	fd = open("src/kernel.cl", O_RDONLY);
	if (fd < 0)
		return (NULL);
	source = (char *)malloc(sizeof(char) * (8192 + 1));
	if (source == NULL)
		return (NULL);
	ret = read(fd, source, 8192);
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
	cl->kernel = clCreateKernel(cl->program, "draw_fractal", NULL);
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
	int		fract_type;

	fract_type = get_fract_type(data);
	clSetKernelArg(data->cl.kernel, 0, sizeof(data->cl.buffer)
			, &data->cl.buffer);
	clSetKernelArg(data->cl.kernel, 1, sizeof(int), &fract_type);
	clSetKernelArg(data->cl.kernel, 2, sizeof(int), &(data->winsize.width));
	clSetKernelArg(data->cl.kernel, 3, sizeof(int), &(data->winsize.height));
	clSetKernelArg(data->cl.kernel, 4, sizeof(int), &(data->cam.x_off));
	clSetKernelArg(data->cl.kernel, 5, sizeof(int), &(data->cam.y_off));
	clSetKernelArg(data->cl.kernel, 6, sizeof(double), &(data->cam.x_min));
	clSetKernelArg(data->cl.kernel, 7, sizeof(double), &(data->cam.x_max));
	clSetKernelArg(data->cl.kernel, 8, sizeof(double), &(data->cam.y_min));
	clSetKernelArg(data->cl.kernel, 9, sizeof(double), &(data->cam.y_max));
	clSetKernelArg(data->cl.kernel, 10, sizeof(double), &(data->motion.x));
	clSetKernelArg(data->cl.kernel, 11, sizeof(double), &(data->motion.y));
	clSetKernelArg(data->cl.kernel, 12, sizeof(int), &(data->max_iters));
	clSetKernelArg(data->cl.kernel, 13, sizeof(int), &(data->sampling));
	clSetKernelArg(data->cl.kernel, 14, sizeof(int), &(data->color_mul));
	clEnqueueNDRangeKernel(data->cl.queue, data->cl.kernel, 1, NULL
			, &data->cl.work_size, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(data->cl.queue, data->cl.buffer, CL_FALSE, 0
			, sizeof(int) * (data->winsize.width * data->winsize.height)
			, data->lib.img_data, 0, NULL, NULL);
	clFinish(data->cl.queue);
}
