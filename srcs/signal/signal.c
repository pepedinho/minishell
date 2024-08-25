/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:20:26 by madamou           #+#    #+#             */
/*   Updated: 2024/08/25 20:08:38 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	set_signal_child(void)
{
	rl_event_hook = sig_event;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

void	set_signal_parent_exec(void)
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

void	set_signal_parent(void)
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
