/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:51:18 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/19 14:22:50 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/Xlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

// struct to represent a node
typedef struct s_node
{
	int		color;
	int		x;
	int		y;
	int		z;
	int		xiso;
	int		yiso;
}			t_node;

// struct to store the data about view the map
typedef struct s_cam
{
	double	zoom;
	double	z_scale;
	double	angle;
	double	x_off;
	double	y_off;
	int		color_mode;
}			t_cam;

// struct to implement the image of minilibx
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

// struct to store the needed data we need to use
typedef struct s_fdf
{
	int		width;
	int		height;
	int		infile;
	int		z_min;
	int		z_max;
	t_node	**matrix;
	t_cam	*data_cam;
	t_img	*data_img;
	char	**tokens;
	void	*mlx_ptr;
	void	*win_ptr;
}			t_fdf;

// struct to store data to make the bresenham
typedef struct s_bresenham
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		e2_val;
	int		x_c;
	int		y_c;
}			t_bresenham;

// struct to store data to set color in nodes
typedef struct s_color
{
	t_node	*a;
	t_node	*b;
	int		x;
	int		y;
	int		color_mode;
	double	r_f;
	double	g_f;
	double	b_f;
	int		r;
	int		g;
	int		b_;
}			t_color;

// calculations_bonus.c
void		ft_calculate_isos(t_fdf *file_map);
double		ft_get_percent(int start, int end, int current);
int			ft_interpolate(int start, int end, double t);
int			ft_get_color(t_color *conf);
// cleanup_bonus.c a
int			ft_close(t_fdf *fdf);
void		ft_error(char *msg, int exit_code);
void		ft_free_and_exit(t_fdf *file_map, char *msg, int exit_code,
				int from_my_code);
void		ft_free_split_tokens(char ***tokens);
void		ft_free_split_matrix(t_node **nodes, int height);
// fdf_bonus.c
int			main(int argc, char **argv);
// parse_and_store_utils_bonus.c
void		ft_malloc_matrix_memory(t_fdf *file_map);
int			is_valid_hex(const char *str);
int			parse_token(t_node *node, char *token);
// parse_and_store_bonus.c
int			ft_store_data(t_fdf *fdf, int width, int row, char **tokens);
int			ft_process_line_aux(int row, char **tokens, t_fdf *map, int mode);
void		process_line(char *line, t_fdf *fdf, int row, int mode);
void		ft_read_file(t_fdf *file_map, int mode, int row);
void		ft_validate_and_store(char *file, t_fdf *file_map);
// draw_bonus.c
void		ft_draw_map(t_fdf *file_map);
void		ft_draw_map_aux(t_fdf *f_map);
void		img_put_pixel(t_img *img, int x, int y, int color);
void		ft_init_bresenham(t_bresenham *b, t_node *a, t_node *b_node);
void		ft_draw_bresenham(t_img *img, t_node *a, t_node *b, int color_mode);
// draw_utils_bonus.c
void		ft_set_color_config_values(t_node *a, t_node *b, t_color *conf,
				t_bresenham *b_data);
void		ft_find_z_min_max(t_fdf *fdf);
int			ft_get_color_from_z(int z, t_fdf *fdf);
void		ft_assign_color_by_z(t_fdf *fdf);

// hooks_bbnus.c
int			ft_handle_keypress(int keycode, t_fdf *fdf);
int			ft_handle_zoom(int keycode, int x, int y, void *param);

#endif
