/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:58:26 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 15:29:20 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_white_space(char *str, int *i)
{
	while (str[*i] == ' ')
		++(*i);
}

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_free_2d(char **split)
{
	int i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
	split = NULL;
}