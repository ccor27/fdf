/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 12:57:09 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-25 12:57:09 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "minilibx/mlx.h"
#include <stdlib.h>
#include <fcntl.h> //open

typedef struct s_node
{
	int	color;
	int	x;
	int	y;
	int	z;
} t_node;

typedef struct  s_map
{
	int	width;
	int	height;
	int	infile;
	t_node **matrix;
	char	**tokens;
} t_file_map;

//error_handler.c
void	ft_error(char *msg, int exit_code);
void	ft_error_parse(t_file_map *file_map, char *msg, int exit_code);
void	ft_free_split_tokens(char **tokens);
void	ft_free_split_matrix(t_node **nodes);
//fdf.c
int	main(int argc, char **argv);
//parse_and_store_utils.c
void	ft_malloc_matrix_memory(t_file_map *file_map);
int	parse_token(t_node *node, char *token, int x, int y);
//parse_and_store.c
void	ft_validate_and_store(char *file, t_file_map *file_map);


#endif
