/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:56:43 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 16:09:10 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_status(int status)
{
	if (WIFEXITED(status))
		g_signal_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal_code = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		g_signal_code = 128 + WSTOPSIG(status);
}