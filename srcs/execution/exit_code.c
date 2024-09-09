/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:56:43 by madamou           #+#    #+#             */
/*   Updated: 2024/09/09 04:02:22 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_status(int status, t_info *info)
{
	if (WIFSIGNALED(status))
	{
		info->signal_code = 128 + WTERMSIG(status);
		info->signaled = 1;
	}
	else if (WIFEXITED(status))
		info->signal_code = WEXITSTATUS(status);
	else if (WIFSTOPPED(status))
		info->signal_code = 128 + WSTOPSIG(status);
}
