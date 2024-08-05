/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:01:22 by madamou           #+#    #+#             */
/*   Updated: 2024/08/06 01:44:35 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **args, t_info *info)
{
	int	i;

	if (args[1])
	{
		if (ft_strcmp(args[1], "-n") == 0)
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
		else if (ft_strcmp(args[1], "?") == 0)
			printf("%d\n", info->signal_code);
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
			ft_printf("\n");
		}
	}
	info->signal_code = 0;
}
