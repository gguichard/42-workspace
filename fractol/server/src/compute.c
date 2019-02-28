/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:04:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/28 17:04:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "opencl.h"
#include "fractol.h"

static void	run_kernel(t_data *data, t_cl *cl, int *buffer)
{
	clSetKernelArg(cl->kernel, 0, sizeof(cl->buffer), &cl->buffer);
	clSetKernelArg(cl->kernel, 1, sizeof(int), &(data->type));
	clSetKernelArg(cl->kernel, 2, sizeof(int), &(data->width));
	clSetKernelArg(cl->kernel, 3, sizeof(int), &(data->height));
	clSetKernelArg(cl->kernel, 4, sizeof(int), &(data->x_off));
	clSetKernelArg(cl->kernel, 5, sizeof(int), &(data->y_off));
	clSetKernelArg(cl->kernel, 6, sizeof(double), &(data->x_min));
	clSetKernelArg(cl->kernel, 7, sizeof(double), &(data->x_max));
	clSetKernelArg(cl->kernel, 8, sizeof(double), &(data->y_min));
	clSetKernelArg(cl->kernel, 9, sizeof(double), &(data->y_max));
	clSetKernelArg(cl->kernel, 10, sizeof(double), &(data->motion_x));
	clSetKernelArg(cl->kernel, 11, sizeof(double), &(data->motion_y));
	clSetKernelArg(cl->kernel, 12, sizeof(int), &(data->max_iters));
	clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL, &cl->work_size, NULL
			, 0, NULL, NULL);
	clEnqueueReadBuffer(cl->queue, cl->buffer, CL_FALSE, 0
			, sizeof(int) * data->width * data->height, buffer, 0, NULL
			, NULL);
	clFinish(cl->queue);
}

void		compute_fractal(t_data *data, const char *source, int *buffer)
{
	t_cl	cl;

	cl.work_size = data->width * data->height;
	clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &cl.device, NULL);
	cl.context = clCreateContext(NULL, 1, &cl.device, NULL, NULL, NULL);
	cl.queue = clCreateCommandQueue(cl.context, cl.device, 0, NULL);
	cl.program = clCreateProgramWithSource(cl.context, 1, (const char **)&source
			, NULL, NULL);
	clBuildProgram(cl.program, 0, NULL, NULL, NULL, NULL);
	cl.kernel = clCreateKernel(cl.program, "draw_fractal", NULL);
	cl.buffer = clCreateBuffer(cl.context, CL_MEM_WRITE_ONLY
			, sizeof(int) * data->width * data->height, NULL
			, NULL);
	run_kernel(data, &cl, buffer);
	clReleaseKernel(cl.kernel);
	clReleaseMemObject(cl.buffer);
	clReleaseCommandQueue(cl.queue);
	clReleaseContext(cl.context);
}
