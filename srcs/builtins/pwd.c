/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:16:53 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 21:55:09 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

void	error_pwd(char *buffer, t_info *info)
{
	free(buffer);
	if (errno == ENOENT)
	{
		ft_fprintf(2, "pwd: error retrieving current directory: ");
		ft_fprintf(2, "getcwd: cannot access parent directories: ");
	}
	perror("pwd");
	info->signal_code = 1;
}

char	*ft_pwd(int cas, t_info *info)
{
	char	*buffer;
	size_t	size;
	char	*check;

	size = 1000;
	check = NULL;
	while (!check)
	{
		size *= 2;
		buffer = malloc(sizeof(char) * size);
		if (!buffer)
			handle_malloc_error("pwd");
		ft_memset(buffer, 0, size);
		check = getcwd(buffer, size);
		if (!check && errno == ERANGE)
			free(buffer);
		else if (!check && errno != ERANGE)
		{
			error_pwd(buffer, info);
			return (NULL);
		}
	}
	if (cas == PRINT)
		(ft_printf("%s\n", buffer), free(buffer));
	info->signal_code = 0;
	return (buffer);
}
