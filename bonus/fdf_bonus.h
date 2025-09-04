/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-04 12:51:18 by crosorio          #+#    #+#             */
/*   Updated: 2025-09-04 12:51:18 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <X11/Xlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_node
{
	int		color;
	int		x;
	int		y;
	int		z;
	int		xiso;
	int		yiso;
}			t_node;

typedef struct s_cam
{
	double	zoom;
	double	z_scale;
	double	angle;
	double	x_off;
	double	y_off;
}			t_cam;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}			t_img;

typedef struct s_fdf
{
	int		width;
	int		height;
	int		infile;
	t_node	**matrix;
	t_cam	*data_cam;
	t_img	*data_img;
	char	**tokens;
	void	*mlx_ptr;
	void	*win_ptr;
}			t_fdf;

typedef struct s_bresenham
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}			t_bresenham;

#endif
