/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:11:50 by madamou           #+#    #+#             */
/*   Updated: 2024/08/03 15:25:49 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	ft_cd(char *directory)
{
	t_info	*info;
	char	*message;

	info = info_in_static(NULL, GET);
	g_signal_code = 0;
	if (chdir(directory) == -1)
	{
		message = ft_sprintf("%s: %s", info->name, directory);
		if (!message)
			handle_malloc_error("cd");
		perror(message);
		free(message);
		g_signal_code = 1;
	}
	return (g_signal_code);
}
