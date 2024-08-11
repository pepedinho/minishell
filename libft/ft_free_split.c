/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:04:52 by madamou           #+#    #+#             */
/*   Updated: 2024/08/11 01:12:04 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_split(char **split)
{
	int	index;

	index = 0;
	while (split[index])
	{
		ft_free(split[index]);
		index++;
	}
	ft_free(split);
	return (1);
}
