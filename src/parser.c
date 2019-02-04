/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 12:25:28 by rejocic           #+#    #+#             */
/*   Updated: 2019/01/28 12:25:30 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf3d.h"

int		sizecheck(t_mlx *mlx)
{
	if ((int)ft_strlen(mlx->charrow) != mlx->cords.max_x)
		return (0);
	else
		return (1);
}

int		contcheck(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->charrow[i])
	{
		if (mlx->charrow[i] == '0' || mlx->charrow[i] == '1')
			i++;
		else
			return (0);
	}
	return (1);
}

char	**ft_realloc(char **arr, int i, t_mlx *mlx)
{
	char	**new_arr;
	int		j;

	new_arr = (char **)malloc((i + 2) * sizeof(char *));
	if (new_arr == NULL)
		shut(mlx);
	j = -1;
	while (++j < i)
		new_arr[j] = arr[j];
	if (i > 0 && arr != NULL)
		free(arr);
	return (new_arr);
}

void	parse_in(t_mlx *mlx, char **line)
{
	char	*tmp;
	int		y;
	int		x;

	tmp = *line;
	y = ft_atoi(tmp);
	while (*tmp != '\0' && *tmp != ',')
		tmp++;
	if (*tmp == ',')
		tmp++;
	else
	{
		ft_putstr("Invalid input: first line should be of the form y,x\n");
		shut(mlx);
	}
	x = ft_atoi(tmp);
	mlx->place[0] = y + 0.5;
	mlx->place[1] = x + 0.5;
	ft_strdel(line);
}

char	**parsefunc(int fd, t_mlx *mlx)
{
	int		i;
	char	*line;

	i = 0;
	mlx->cords.max_x = -7;
	mlx->chararr = NULL;
	if (get_next_line(fd, &line) == 1)
		parse_in(mlx, &line);
	else
		return (0);
	while (get_next_line(fd, &line) == 1)
	{
		mlx->chararr = ft_realloc(mlx->chararr, i, mlx);
		mlx->chararr[i + 1] = NULL;
		mlx->charrow = ft_strdup(line);
		free(line);
		if (mlx->cords.max_x == -7)
			mlx->cords.max_x = ft_strlen(mlx->charrow);
		if (sizecheck(mlx) == 0 || contcheck(mlx) == 0)
			return (0);
		mlx->chararr[i++] = mlx->charrow;
	}
	mlx->cords.max_y = i;
	return (mlx->chararr);
}
