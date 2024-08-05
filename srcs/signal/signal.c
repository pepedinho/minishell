/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:20:26 by madamou           #+#    #+#             */
/*   Updated: 2024/08/05 19:37:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	handle_sigint(int num)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	info->signal_code = num + 128;
	write(STDERR_FILENO, "\n", 1);
	if (g_sigint_received == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	kill_child(int num)
// {
// 	t_info *info;

// 	info = info_in_static(NULL, GET);
// 	info->signal_code = num + 128;
// 	if (g_is_child == 1)
// 	{
// 		exit(num);
// 	}
// 	else
// 	{
// 		write(STDERR_FILENO, "\n", 1);
// 	}
// }

void	kill_if_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	sigaction_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sb, 0, sizeof(sb));
	sb.sa_handler = SIG_IGN;
	sb.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sb, NULL);
}
