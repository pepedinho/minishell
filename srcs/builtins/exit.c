/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:31:28 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 17:18:58 by madamou          ###   ########.fr       */
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
	t_info	*info;

	info = info_in_static(NULL, GET);
	ft_fprintf(2, "exit\n");
	if (!args)
		free_and_exit(0);
	if (args[1])
	{
		if (ft_is_numeric(args[1]) == 0)
		{
			ft_fprintf(2, "%s: exit: %s: numeric argument required\n",
					info->name, args[1]);
			free_and_exit(EXIT_FAILURE);
		}
		if (!args[2])
			free_and_exit((unsigned char)ft_atoi(args[1]));
		ft_fprintf(2, "%s: exit: too many arguments\n", info->name);
		return ;
	}
	free_and_exit(g_signal_code);
}
