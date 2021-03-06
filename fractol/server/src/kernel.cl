#define JULIA 1
#define JULIA3 2
#define MANDELBROT 3
#define MANDELBROT3 4
#define MANDELBAR 5
#define BURNING_SHIP 6
#define CUSTOMBROT 7
#define CUSTOMBROT2 8

int	get_fract_color(int iters)
{
	int colors[] = {
		0x421e0f, 0x19071a, 0x09012f, 0x040449,
		0x000764, 0x022c8a, 0x1852b1, 0x397dd1,
		0x86b5e5, 0xd3ecf8, 0xf1e9bf, 0xf8c95f,
		0xffaa00, 0xcc8000, 0x995700, 0x6a3403
	};
	return (colors[iters % 16]);
}

int	fract_bailout(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp = 0.0;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = x;
		x = x2 - y2 + re;
		y = 2 * x_tmp * y + im;
		iters++;
	}
	return (iters);
}

int	fract_bailout_custom(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	re2, im2;
	double	a, b;

	iters = 0;
	re2 = re * re;
	im2 = im * im;
	while (iters < max_iters)
	{
		if (x * x + y * y >= 2500)
			break ;
		a = (x * re + y * im) / (re2 + im2);
		b = (y * re - x * im) / (re2 + im2);
		x = cos(a) * cosh(b);
		y = -sin(a) * sinh(b);
		iters++;
	}
	return (iters);
}

int	fract_bailout_custom_2(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	re2, im2;
	double	x_tmp;

	iters = 0;
	re2 = re * re;
	im2 = im * im;
	while (iters < max_iters)
	{
		if (x * x + y * y >= 75)
			break ;
		x_tmp = x;
		x = re / (re2 + im2) + cos(x) * cosh(y);
		y = -sin(x_tmp) * sinh(y) + im / (re2 + im2);
		iters++;
	}
	return (iters);
}

int	fract_bailout_pow3(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	x2, x3;
	double	y2, y3;
	double	x_tmp;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		x3 = x2 * x;
		y2 = y * y;
		y3 = y2 * y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = x;
		x = x3 - 3 * x_tmp * y2 + re;
		y = 3 * x2 * y - y3 + im;
		iters++;
	}
	return (iters);
}

int	fract_bailout_2(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp = 0.0;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = x;
		x = fabs(x2 - y2 + re);
		y = fabs(2 * x_tmp * y) + im;
		iters++;
	}
	return (iters);
}

int	fract_inv_bailout(double x, double y, double re, double im, int max_iters)
{
	int		iters;
	double	x2;
	double	y2;
	double	x_tmp = 0.0;

	iters = 0;
	while (iters < max_iters)
	{
		x2 = x * x;
		y2 = y * y;
		if (x2 + y2 >= 4)
			break ;
		x_tmp = x;
		x = x2 - y2 + re;
		y = -2 * x_tmp * y + im;
		iters++;
	}
	return (iters);
}

__kernel void draw_fractal(__global int *data, int type, int width, int height
		, int x_off, int y_off, double x_min, double x_max, double y_min, double y_max
		, double motion_x, double motion_y, int max_iters, int sampling)
{
	int		global_id;
	int		idx;
	double	re;
	double	im;
	int		color;
	int		r_total;
	int		g_total;
	int		b_total;
	int		iters;

	global_id = get_global_id(0);
	idx = 0;
	r_total = 0;
	g_total = 0;
	b_total = 0;
	while (idx < sampling * sampling)
	{
		iters = 0;
		re = ((global_id % width) * sampling + (idx % sampling) + x_off) * (x_max - x_min) / (width * sampling) + x_min;
		im = ((global_id / width) * sampling + (idx / sampling) + y_off) * (y_max - y_min) / (height * sampling) + y_min;
		switch (type)
		{
			case JULIA:
				iters = fract_bailout(re, im, motion_x, motion_y, max_iters);
				break ;
			case JULIA3:
				iters = fract_bailout_pow3(re, im, motion_x, motion_y, max_iters);
				break ;
			case MANDELBROT:
				iters = fract_bailout(0, 0, re, im, max_iters);
				break ;
			case CUSTOMBROT:
				iters = fract_bailout_custom(0, 0, re, im, max_iters);
				break ;
			case CUSTOMBROT2:
				iters = fract_bailout_custom_2(0, 0, re, im, max_iters);
				break ;
			case MANDELBROT3:
				iters = fract_bailout_pow3(0, 0, re, im, max_iters);
				break ;
			case MANDELBAR:
				iters = fract_inv_bailout(0, 0, re, im, max_iters);
				break ;
			case BURNING_SHIP:
				iters = fract_bailout_2(0, 0, re, im, max_iters);
				break ;
		}
		color = (iters == max_iters) ? 0 : get_fract_color(iters);
		r_total += (color >> 16) & 0xFF;
		g_total += (color >> 8) & 0xFF;
		b_total += color & 0xFF;
		idx++;
	}
	r_total /= idx;
	g_total /= idx;
	b_total /= idx;
	data[global_id] = ((r_total << 16) | (g_total << 8) | b_total);
}
