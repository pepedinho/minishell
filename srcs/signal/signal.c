/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:20:26 by madamou           #+#    #+#             */
/*   Updated: 2024/08/18 22:38:11 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void check_if_signal(void)
{
	if (g_signal == 128 + SIGQUIT)
       		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (g_signal == 128 + SIGINT)
		write(STDERR_FILENO, "\n", 1);
	g_signal = 0;
}

void	handle_signal_parent(int num)
{
	g_signal = num + 128;
}

static int    sig_event(void)
{
    return (EXIT_SUCCESS);
}

void if_sigint(int sig)
{
	g_signal = 128 + sig;
	rl_done = 1;
}

void set_signal_child(void)
{
	rl_event_hook = sig_event;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

void set_signal_parent_exdsdec(void)
{
	rl_event_hook = sig_event;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}


void set_signal_parent_exec(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	rl_event_hook = sig_event;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_signal_parent;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sb, 0, sizeof(sb));
	sb.sa_handler = handle_signal_parent;
	sb.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sb, NULL);
}

void set_signal_parent(void)
{
	struct sigaction	sa;

	rl_event_hook = sig_event;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = if_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
