/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:20:26 by madamou           #+#    #+#             */
/*   Updated: 2024/07/26 15:28:21 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"
#include <signal.h>

void handle_sigint(int num)
{
	(void)num;
	write(STDERR_FILENO, "minishell > ^C\nminishell > ", 27);
}

void sigaction_sigint(void)
{
	struct sigaction sa;

	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
