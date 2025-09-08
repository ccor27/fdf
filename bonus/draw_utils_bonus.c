/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-07 14:01:25 by crosorio          #+#    #+#             */
/*   Updated: 2025-09-07 14:01:25 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_set_color_config_values(t_node *a, t_node *b, t_color *conf,
		t_bresenham *b_data)
{
	conf->a = a;
	conf->b = b;
	conf->x = b_data->x_c;
	conf->y = b_data->y_c;
}
