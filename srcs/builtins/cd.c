/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:11:50 by madamou           #+#    #+#             */
/*   Updated: 2024/08/03 15:22:40 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	ft_cd(char *directory)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	g_signal_code = 0;
	if (chdir(directory) == -1)
	{
		perror(ft_sprintf("%s: %s", info->name, directory));
		g_signal_code = 1;
	}
	return (g_signal_code);
}
