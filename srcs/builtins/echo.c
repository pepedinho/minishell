/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:01:22 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 01:07:09 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **args)
{
	int	i;

	if (ft_strcmp(args[1], "-n") != 0)
	{
		i = 2;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			if (args[i + 1])
				ft_printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			if (args[i + 1])
				ft_printf(" ");
			i++;
		}
	}
	g_signal_code = 0;
}
