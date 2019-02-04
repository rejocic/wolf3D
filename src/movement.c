/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:28:55 by rejocic           #+#    #+#             */
/*   Updated: 2019/01/31 15:29:04 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

void		refresh_angle(t_mlx *mlx)
{
	mlx->dir[0] = sin(mlx->theta);
	mlx->dir[1] = cos(mlx->theta);
	mlx->perp_dir[0] = -1. * cos(mlx->theta);
	mlx->perp_dir[1] = sin(mlx->theta);
}

void		strafe(double speed, t_mlx *mlx)
{
	if (mlx->flags & HROTATE)
	{
		if (RIGHTSHIFTED(0) < mlx->cords.max_y && RIGHTSHIFTED(0) >= 0 && \
		mlx->chararr[RIGHTSHIFTED(0)][(int)floor(mlx->place[1])] == '0')
			mlx->place[0] -= speed * mlx->perp_dir[0];
		if (RIGHTSHIFTED(1) < mlx->cords.max_x && RIGHTSHIFTED(1) >= 0 && \
		mlx->chararr[(int)floor(mlx->place[0])][RIGHTSHIFTED(1)] == '0')
			mlx->place[1] -= speed * mlx->perp_dir[1];
	}
	if (mlx->flags & HROTATEB)
	{
		if (LEFTSHIFTED(0) < mlx->cords.max_y && LEFTSHIFTED(0) >= 0 && \
		mlx->chararr[LEFTSHIFTED(0)][(int)floor(mlx->place[1])] == '0')
			mlx->place[0] += speed * mlx->perp_dir[0];
		if (LEFTSHIFTED(1) < mlx->cords.max_x && LEFTSHIFTED(1) >= 0 && \
		mlx->chararr[(int)floor(mlx->place[0])][LEFTSHIFTED(1)] == '0')
			mlx->place[1] += speed * mlx->perp_dir[1];
	}
}

void		move(double speed, t_mlx *mlx)
{
	if (mlx->flags & FORWARD)
	{
		if (UPSHIFTED(0) < mlx->cords.max_y && UPSHIFTED(0) >= 0 && \
		mlx->chararr[UPSHIFTED(0)][(int)floor(mlx->place[1])] == '0')
			mlx->place[0] += speed * mlx->dir[0];
		if (UPSHIFTED(1) < mlx->cords.max_x && UPSHIFTED(1) >= 0 && \
		mlx->chararr[(int)floor(mlx->place[0])][UPSHIFTED(1)] == '0')
			mlx->place[1] += speed * mlx->dir[1];
	}
	if (mlx->flags & BACK)
	{
		if (DOWNSHIFTED(0) < mlx->cords.max_y && DOWNSHIFTED(0) >= 0 && \
		mlx->chararr[DOWNSHIFTED(0)][(int)floor(mlx->place[1])] == '0')
			mlx->place[0] -= speed * mlx->dir[0];
		if (DOWNSHIFTED(1) < mlx->cords.max_x && DOWNSHIFTED(1) >= 0 && \
		mlx->chararr[(int)floor(mlx->place[0])][DOWNSHIFTED(1)] == '0')
			mlx->place[1] -= speed * mlx->dir[1];
	}
}

int			refresh_window(t_mlx *mlx)
{
	double	speed;
	double	rot_speed;

	speed = ((mlx->flags & SPRINT) ? SPEED * BOOST : SPEED);
	rot_speed = ((mlx->flags & SPRINT) ? HRSPEED * BOOST : HRSPEED);
	refresh_angle(mlx);
	if (mlx->flags & STRAFE)
		strafe(speed, mlx);
	else
	{
		if (mlx->flags & HROTATE)
			mlx->theta = fmod(mlx->theta + rot_speed, 2 * M_PI);
		if (mlx->flags & HROTATEB)
			mlx->theta = fmod(mlx->theta + 2 * M_PI - rot_speed, 2 * M_PI);
	}
	move(speed, mlx);
	draw(mlx);
	return (0);
}

void		make_textures(int texts[4][64][64], int i, int j)
{
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			if (abs(i - j) % 3)
				texts[0][i][j] = 0xffccee;
			else
				texts[0][i][j] = 0x669988;
			if ((i + j) % 2)
				texts[1][i][j] = 0xeeccff;
			else
				texts[1][i][j] = 0x668899;
			if (i * j < 256)
				texts[2][i][j] = 0xcceeff;
			else
				texts[2][i][j] = 0x886699;
			if (i / (j + 1.) < 2.5)
				texts[3][i][j] = 0xccffee;
			else
				texts[3][i][j] = 0x996688;
		}
	}
}
