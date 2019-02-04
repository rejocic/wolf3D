/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rejocic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 11:05:41 by rejocic           #+#    #+#             */
/*   Updated: 2019/01/24 11:05:44 by rejocic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIDTH 720
# define HEIGHT 720

# define STRAFE (1 << 0)
# define HROTATE (1 << 1)
# define FORWARD (1 << 2)
# define HROTATEB (1 << 3)
# define BACK (1 << 4)
# define SPRINT (1 << 5)

# define MARGIN 0.05
# define SPEED 0.06
# define BOOST 2.
# define HRSPEED 0.03

# define NONSHIFTED(y) (int)floor(mlx->place[y])
# define UPSHIFTED(y) (int)floor(mlx->place[y] + speed * mlx->dir[y])
# define DOWNSHIFTED(y) (int)floor(mlx->place[y] - speed * mlx->dir[y])
# define LEFTSHIFTED(y) (int)floor(mlx->place[y] + speed * mlx->perp_dir[y])
# define RIGHTSHIFTED(y) (int)floor(mlx->place[y] - speed * mlx->perp_dir[y])

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <math.h>

typedef struct		s_ray
{
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			sdist_x;
	double			sdist_y;
	double			ddist_x;
	double			ddist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	int				hit;
	int				side;
	int				line_height;
	int				norm;
}					t_ray;

typedef struct		s_cords
{
	int				max_x;
	int				max_y;

}					t_cords;

typedef struct		s_mlx
{
	int				texts[4][64][64];
	int				bpp;
	int				lsize;
	int				endian;
	char			*addr;
	unsigned char	flags;
	double			theta;
	double			place[2];
	double			dir[2];
	double			perp_dir[2];
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			**chararr;
	char			*charrow;
	int				color_ceiling;
	int				color_floor;
	t_cords			cords;
	t_ray			ray;
}					t_mlx;

char				**parsefunc(int fd, t_mlx *mlx);
void				initialread(char *line, t_mlx *mlx);
void				window(t_mlx *mlx);
int					sizecheck(t_mlx *mlx);
int					contcheck(t_mlx *mlx);
int					shut(t_mlx *mlx);
int					key_press(int keycode, t_mlx *mlx);
int					key_release(int keycode, t_mlx *mlx);
void				make_textures(int texts[4][64][64], int i, int j);
int					refresh_window(t_mlx *mlx);
void				strafe(double speed, t_mlx *mlx);
void				move(double speed, t_mlx *mlx);
void				refresh_angle(t_mlx *mlx);
void				draw(t_mlx *mlx);
int					color_blend(int c1, int c2, double ratio);
void				ft_put_pixel(t_mlx *mlx, int x, int y, int color);
void				vertttline(int x, t_mlx *mlx, int norm, int ind);
int					color_of(int text[64][64], int x, double y);
void				wallfinder(t_mlx *mlx);
void				whichside(int x, t_mlx *mlx);
void				drawline(int x, t_mlx *mlx);

#endif
