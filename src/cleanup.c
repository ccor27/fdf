/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 13:32:12 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-25 13:32:12 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_fdf *fdf)
{
	ft_free_and_exit(fdf, NULL, 0, 1);
	return (0);
}

void	ft_error(char *msg, int exit_code)
{
	if (msg)
		ft_printf("\033[0;31m%s\033[0m", msg);
	exit(exit_code);
}

void	ft_free_and_exit(t_fdf *fdf, char *msg, int exit_code, int from_my_code)
{
	if (fdf->matrix)
		ft_free_split_matrix(fdf->matrix, fdf->height);
	if (fdf->infile > 0)
		close(fdf->infile);
	if (fdf->data_cam)
		free(fdf->data_cam);
	if (fdf->data_img)
	{
		if (fdf->data_img->img)
			mlx_destroy_image(fdf->mlx_ptr, fdf->data_img->img);
	}
	if (from_my_code && fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	ft_error(msg, exit_code);
}

void	ft_free_split_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	tokens = NULL;
}

void	ft_free_split_matrix(t_node **nodes, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(nodes[i]);
		i++;
	}
	free(nodes);
}
