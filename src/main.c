/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:00:49 by rejocic           #+#    #+#             */
/*   Updated: 2019/01/27 14:00:51 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int			shut(t_mlx *mlx)
{
	int	i;

	if (mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr != NULL)
		free(mlx->mlx_ptr);
	i = 0;
	if (mlx->chararr != NULL)
	{
		while (mlx->chararr[i] != NULL)
			free(mlx->chararr[i++]);
		free(mlx->chararr);
	}
	free(mlx);
	exit(0);
	return (0);
}

void		initialize(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Hell");
	mlx->theta = M_PI / 4.;
	mlx->flags = 0;
	ft_bzero(mlx->texts, 4 * 64 * 64 * sizeof(int));
	make_textures(mlx->texts, -1, -1);
}

void		window(t_mlx *mlx)
{
	int		i;

	i = 0;
	if (mlx->place[0] < 0. || mlx->place[0] > mlx->cords.max_y ||
		mlx->place[1] < 0. || mlx->place[1] > mlx->cords.max_x ||
		mlx->chararr[NONSHIFTED(0)][NONSHIFTED(1)] != '0')
	{
		ft_putstr("Invalid input: must start in empty square\n");
		shut(mlx);
	}
	initialize(mlx);
	mlx_hook(mlx->win_ptr, 17, 0, shut, mlx);
	mlx_hook(mlx->win_ptr, 2, 0, key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 0, key_release, mlx);
	mlx_loop_hook(mlx->mlx_ptr, refresh_window, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_mlx	*mlx;

	if (argc == 2)
	{
		mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx));
		if ((fd = open(argv[1], O_RDONLY)) < 0)
		{
			ft_putstr("Error: input must be a file\n");
			return (0);
		}
		if (parsefunc(fd, mlx) == 0)
		{
			ft_putstr("Not a valid map, please try again\n");
			return (0);
		}
		window(mlx);
		shut(mlx);
	}
	else if (argc > 2)
		ft_putstr("Too many input files, please enter only one map\n");
	else if (argc < 2)
		ft_putstr("No input given, please enter a map file\n");
	return (0);
}
