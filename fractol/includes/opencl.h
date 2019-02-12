/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 03:53:42 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/12 04:31:23 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_H
# define OPENCL_H

# include <OpenCL/opencl.h>

typedef struct			s_cl
{
	char				*source;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				buffer;
	size_t				work_size;
}						t_cl;

#endif
