/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:31:28 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 15:53:10 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_numeric(char *nb)
{
	int	i;

	i = 0;
	while (nb[i])
	{
		if (ft_isdigit(nb[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	t_info *info;

	info = info_in_static(NULL, GET);
	ft_printf("exit\n");
	if (args[1])
	{
		if (ft_is_numeric(args[1]) == 0)
		{
			ft_fprintf(2, "%s: exit: %s: numeric argument required\n",
					info->name, args[1]);
			exit(EXIT_FAILURE);
		}
		if (!args[2])
			exit((char)ft_atoi(args[1]));
		ft_fprintf(2, "%s: exit: too many arguments\n", info->name);
		return ;
	}
	exit(g_signal_code);
}