/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imagination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:38:51 by rejocic           #+#    #+#             */
/*   Updated: 2019/01/30 13:38:53 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

void		whichside(int x, t_mlx *mlx)
{
	if (!mlx->ray.side)
	{
		mlx->ray.norm = (int)(fmod(fabs(mlx->ray.sdist_x - mlx->ray.sdist_y \
		- mlx->ray.ddist_x), mlx->ray.ddist_y) * 64. / mlx->ray.ddist_y);
		if (mlx->ray.ray_dir_y > 0)
			mlx->ray.norm = 63 - mlx->ray.norm;
		if (mlx->ray.step_x + 1)
			vertttline(x, mlx, mlx->ray.norm, 0);
		else
			vertttline(x, mlx, mlx->ray.norm, 1);
	}
	else
	{
		mlx->ray.norm = (int)(fmod(fabs(mlx->ray.sdist_y - mlx->ray.sdist_x \
		- mlx->ray.ddist_y), mlx->ray.ddist_x) * 64. / mlx->ray.ddist_x);
		if (mlx->ray.ray_dir_x > 0)
			mlx->ray.norm = 63 - mlx->ray.norm;
		if (mlx->ray.step_y + 1)
			vertttline(x, mlx, mlx->ray.norm, 2);
		else
			vertttline(x, mlx, mlx->ray.norm, 3);
	}
	return ;
}

void		wallfinder(t_mlx *mlx)
{
	if (mlx->ray.sdist_x < mlx->ray.sdist_y)
	{
		mlx->ray.sdist_x += mlx->ray.ddist_x;
		mlx->ray.map_x += mlx->ray.step_x;
		mlx->ray.side = 0;
	}
	else
	{
		mlx->ray.sdist_y += mlx->ray.ddist_y;
		mlx->ray.map_y += mlx->ray.step_y;
		mlx->ray.side = 1;
	}
	if (mlx->ray.map_x < 0 || mlx->ray.map_x >= mlx->cords.max_x || \
	mlx->ray.map_y < 0 || mlx->ray.map_y >= mlx->cords.max_y || \
	mlx->chararr[mlx->ray.map_y][mlx->ray.map_x] != '0')
		mlx->ray.hit = 1;
	return ;
}

void		drawline(int x, t_mlx *mlx)
{
	if (mlx->ray.ray_dir_x < 0)
		mlx->ray.sdist_x = (mlx->place[1] - mlx->ray.map_x) * mlx->ray.ddist_x;
	else
		mlx->ray.sdist_x = (mlx->ray.map_x + 1.0 - mlx->place[1]) * \
		mlx->ray.ddist_x;
	mlx->ray.step_y = (mlx->ray.ray_dir_y >= 0) * 2 - 1;
	if (mlx->ray.ray_dir_y < 0)
		mlx->ray.sdist_y = (mlx->place[0] - mlx->ray.map_y) * \
		mlx->ray.ddist_y;
	else
		mlx->ray.sdist_y = (mlx->ray.map_y + 1.0 - mlx->place[0]) * \
		mlx->ray.ddist_y;
	while (mlx->ray.hit == 0)
		wallfinder(mlx);
	if (mlx->ray.side == 0)
		mlx->ray.perp_wall_dist = (mlx->ray.map_x - mlx->place[1] \
		+ (1 - mlx->ray.step_x) / 2) / mlx->ray.ray_dir_x;
	else
		mlx->ray.perp_wall_dist = (mlx->ray.map_y - mlx->place[0] \
		+ (1 - mlx->ray.step_y) / 2) / mlx->ray.ray_dir_y;
	mlx->ray.line_height = (int)(HEIGHT / (2 * mlx->ray.perp_wall_dist));
	mlx->color_ceiling = 0x770033;
	mlx->color_floor = 0x330077;
	whichside(x, mlx);
	return ;
}

void		draw(t_mlx *mlx)
{
	int		x;

	mlx->ray.plane_x = -0.5 * mlx->perp_dir[1];
	mlx->ray.plane_y = -0.5 * mlx->perp_dir[0];
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img_ptr, &(mlx->bpp), \
	&(mlx->lsize), &(mlx->endian));
	x = -1;
	while (++x < WIDTH)
	{
		mlx->ray.camera_x = 2 * x / (double)WIDTH - 1;
		mlx->ray.ray_dir_x = mlx->dir[1] + mlx->ray.plane_x * mlx->ray.camera_x;
		mlx->ray.ray_dir_y = mlx->dir[0] + mlx->ray.plane_y * mlx->ray.camera_x;
		mlx->ray.map_x = (int)floor(mlx->place[1]);
		mlx->ray.map_y = (int)floor(mlx->place[0]);
		mlx->ray.ddist_x = fabs(1 / mlx->ray.ray_dir_x);
		mlx->ray.ddist_y = fabs(1 / mlx->ray.ray_dir_y);
		mlx->ray.hit = 0;
		mlx->ray.step_x = (mlx->ray.ray_dir_x >= 0) * 2 - 1;
		drawline(x, mlx);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
}
