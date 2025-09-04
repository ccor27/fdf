/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-03 10:36:58 by crosorio          #+#    #+#             */
/*   Updated: 2025-09-03 10:36:58 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
	{
		ft_printf("entro al ft_handle_key_press");
		ft_free_and_exit(fdf, NULL, 0, 0);
	}
	return (0);
}
