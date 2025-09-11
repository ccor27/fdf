/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:57:09 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/11 12:14:07 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/Xlib.h>
# include <fcntl.h> //open
# include <math.h>  // cos and sin
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

// cleanup.c a
int			ft_close(t_fdf *fdf);
void		ft_error(char *msg, int exit_code);
void		ft_free_and_exit(t_fdf *file_map, char *msg, int exit_code,
				int from_my_code);
void		ft_free_split_tokens(char **tokens);
void		ft_free_split_matrix(t_node **nodes, int height);
// fdf.c
void	ft_initialize(t_fdf *file_map);
void	ft_init_cam(t_fdf *fdf);
int	ft_init_mlx(t_fdf *fdf);
int			main(int argc, char **argv);
// parse_and_store_utils.c
void		ft_malloc_matrix_memory(t_fdf *file_map);
int			is_valid_hex(const char *str);
int			ft_is_valid_integer(const char *str);
int			parse_token(t_node *node, char *token);
// parse_and_store.c
void	ft_store_data(t_fdf *file_map, int width, int row, char **tokens);
void	ft_process_line_aux(int row, char **tokens, t_fdf *map, int mode);
void	process_line(char *line, t_fdf *fdf, int row, int mode);
void	ft_read_file(t_fdf *file_map, int mode);
void		ft_validate_and_store(char *file, t_fdf *file_map);
// calculations.c
void		ft_calculate_isos(t_fdf *file_map);
void		img_put_pixel(t_img *img, int x, int y, int color);
void		ft_init_bresenham(t_bresenham *b, t_node *a, t_node *b_node);
void		ft_draw_bresenham(t_img *img, t_node *a, t_node *b);
// hooks.c
int			ft_handle_keypress(int keycode, t_fdf *fdf);
// draw.c
void		ft_draw_map(t_fdf *file_map);
void		ft_draw_map_aux(t_fdf *f_map);
#endif
