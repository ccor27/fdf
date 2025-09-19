/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 15:50:28 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-25 15:50:28 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip_spaces(int *index, const char *str)
{
	while (str[(*index)] == 32 || (str[(*index)] >= 9 && str[(*index)] <= 13))
		(*index)++;
}

int	ft_base_value(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// static int	ft_check_base(const char *base)
// {
// 	int	len;
// 	int	j;

// 	len = 0;
// 	while (base[len])
// 	{
// 		if (base[len] == '+' || base[len] == '-' || (base[len] >= 9
// 				&& base[len] <= 13) || base[len] == 32)
// 			return (0);
// 		j = len + 1;
// 		while (base[j])
// 		{
// 			if (base[len] == base[j])
// 				return (0);
// 			j++;
// 		}
// 		len++;
// 	}
// 	return (len >= 2);
// }
static	int	ft_aux_convertion(const char *base, const char *str, int sign,
		int i)
{
	int	res;
	int	value;
	int	base_len;

	base_len = 16;
	res = 0;
	value = 0;
	while ( value != -1)
	{
		value = ft_base_value(str[i], base);
		res = res * base_len + value;
		i++;
	}
	return (res * sign);
}

int	ft_atoi_base(const char *str, const char *base)
{
	int	sign;
	int	i;

	i = 0;
	ft_skip_spaces(&i, str);
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	};
	return (ft_aux_convertion(base,str,sign,i));
}
