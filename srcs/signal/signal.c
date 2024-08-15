/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:20:26 by madamou           #+#    #+#             */
/*   Updated: 2024/08/15 15:30:34 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void sigchld_handler(int sig) 
{
	(void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void	handle_signal_parent(int num)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	info->signal_code = num + 128;
	if (num == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		if (g_signal == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	if (num == SIGQUIT)
        ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	kill_if_sigint(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sb.sa_handler = SIG_DFL;
	sb.sa_flags = 0;
	sigemptyset(&sb.sa_mask);
	sigaction(SIGQUIT, &sb, NULL);
}
static int    sig_event(void)
{
    return (EXIT_SUCCESS);
}

void	sigaction_signals(int signal, void handler(int))
{
	struct sigaction	sa;

	rl_event_hook = sig_event;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(signal, &sa, NULL);
}
