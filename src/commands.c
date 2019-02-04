/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 15:26:25 by rejocic           #+#    #+#             */
/*   Updated: 2019/01/31 15:26:27 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int			key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 53 || keycode == 51)
		shut(mlx);
	else if (keycode == 6)
		mlx->flags |= STRAFE;
	else if (keycode == 257)
		mlx->flags |= SPRINT;
	else if (keycode == 124)
		mlx->flags |= HROTATE;
	else if (keycode == 126)
		mlx->flags |= FORWARD;
	else if (keycode == 123)
		mlx->flags |= HROTATEB;
	else if (keycode == 125)
		mlx->flags |= BACK;
	return (0);
}

int			key_release(int keycode, t_mlx *mlx)
{
	if (keycode == 6)
		mlx->flags &= ~STRAFE;
	else if (keycode == 257)
		mlx->flags &= ~SPRINT;
	else if (keycode == 124)
		mlx->flags &= ~HROTATE;
	else if (keycode == 126)
		mlx->flags &= ~FORWARD;
	else if (keycode == 123)
		mlx->flags &= ~HROTATEB;
	else if (keycode == 125)
		mlx->flags &= ~BACK;
	return (0);
}
