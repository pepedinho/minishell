/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:01:22 by madamou           #+#    #+#             */
/*   Updated: 2024/08/14 17:53:58 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	all_char_are_the_same(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] != str[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	if_option(char **args, int *i)
{
	int	j;

	j = 0;
	while (args[*i][0] == '-' && args[*i][1] == 'n'
		&& all_char_are_the_same(&args[*i][1]))
	{
		(*i)++;
		j++;
	}
	return (j);
}

void	ft_echo(char **args, t_info *info)
{
	int	i;

	if (args[1])
	{
		i = 1;
		if (if_option(args, &i))
		{
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
