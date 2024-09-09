/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:00:34 by madamou           #+#    #+#             */
/*   Updated: 2024/09/09 04:14:43 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_if_signal(t_info *info)
{
	if (info->signaled == 1 && g_signal == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (g_signal == 128 + SIGINT && info->signaled == 1)
		write(STDERR_FILENO, "\n", 1);
	g_signal = 0;
}

void	handle_signal_parent(int num)
{
	g_signal = num + 128;
}

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	if_sigint(int sig)
{
	g_signal = 128 + sig;
	rl_done = 1;
}

void	set_info_if_signal(t_info *info)
{
	info->signal_code = g_signal;
	g_signal = 0;
}
