/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:04:48 by rejocic           #+#    #+#             */
/*   Updated: 2019/01/31 18:04:57 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int			color_blend(int c1, int c2, double ratio)
{
	int	c3;

	c3 = (unsigned int)round(((c2 >> 8) & 0xff) * ratio +
			((c1 >> 8) & 0xff) * (1 - ratio)) << 8;
	c3 |= (unsigned int)round((c2 & 0xff) * ratio +
			(c1 & 0xff) * (1.0 - ratio));
	c3 |= (unsigned int)round(((c2 >> 16) & 0xff) * ratio +
			((c1 >> 16) & 0xff) * (1 - ratio)) << 16;
	return (c3);
}

void		ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int				j;
	unsigned int	colorval;

	colorval = mlx_get_color_value(mlx->mlx_ptr, color);
	j = 0;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	while (j < (mlx->bpp / 8))
	{
		*(mlx->addr + (mlx->lsize * y + ((mlx->bpp * x) / 8) + j)) = \
		(colorval >> (8 * j)) & 0xff;
		j++;
	}
}

int			color_of(int text[64][64], int x, double y)
{
	return (text[(int)floor(y * 64.)][x]);
}

void		vertttline(int x, t_mlx *mlx, int norm, int ind)
{
	int		i;
	int		mid;
	double	to_add;
	int		drawstart;
	int		drawend;

	i = -1;
	mid = HEIGHT / 2;
	drawstart = mid - mlx->ray.line_height / 2;
	drawend = mid + mlx->ray.line_height / 2;
	while (++i <= HEIGHT)
	{
		to_add = abs(i - mid) * 1. / (drawend - drawstart);
		if (i < drawstart)
			ft_put_pixel(mlx, x, i, color_blend(mlx->color_ceiling, \
			0x2211bb, (mid - i) * 1. / mid));
		else if (i > drawend)
			ft_put_pixel(mlx, x, i, color_blend(mlx->color_floor, \
			0, (HEIGHT - i) * 1. / mid));
		else
			ft_put_pixel(mlx, x, i, color_of(mlx->texts[ind], norm, to_add));
	}
}
