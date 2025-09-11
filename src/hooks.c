/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:36:58 by crosorio          #+#    #+#             */
/*   Updated: 2025/09/11 11:55:16 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		ft_free_and_exit(fdf, NULL, 0, 0);
	return (0);
}
