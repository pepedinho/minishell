/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:31:28 by madamou           #+#    #+#             */
/*   Updated: 2024/09/02 10:51:55 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_numeric(char *nb)
{
	int	i;

	i = 0;
	if (!nb)
		return (0);
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	while (nb[i])
	{
		if (ft_isdigit(nb[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_in_range(char *nb)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (ft_strlen(nb) > 20)
		return (0);
	if (nb[i] == '+' || nb[i] == '-')
		if (nb[i++] == '-')
			sign = -1;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		if (result > 922337203685477580
			|| (sign == 1 && result == 922337203685477580 && nb[i] > '7')
			|| (sign == -1 && result == 922337203685477580 && nb[i] > '8'))
			return (0);
		result *= 10;
		result += (nb[i++] - '0');
	}
	return (1);
}

void	ft_exit(char **args)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	if (info->is_child == 0)
		ft_fprintf(2, "exit\n");
	if (!args)
		free_and_exit(info->signal_code);
	if (args[1])
	{
		if (ft_is_numeric(args[1]) == 0 || ft_is_in_range(args[1]) == 0)
		{
			ft_fprintf(2, "%s: exit: %s: numeric argument required\n",
				info->name, args[1]);
			free_and_exit(2);
		}
		if (!args[2])
			free_and_exit((unsigned char)ft_atoi(args[1]));
		ft_fprintf(2, "%s: exit: too many arguments\n", info->name);
		info->signal_code = 1;
		return ;
	}
	free_and_exit(info->signal_code);
}
