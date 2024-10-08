/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:18:55 by madamou           #+#    #+#             */
/*   Updated: 2024/08/28 23:22:14 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_message(char *content)
{
	t_info	*info;
	char	*message;

	info = info_in_static(NULL, GET);
	message = ft_sprintf("%s: %s", info->name, content);
	perror(message);
	ft_free(message);
	info->signal_code = 1;
}

void	message_pipe(char *limiter, int cpt)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	ft_printf("%s: warning: here-document at line %d delimited ", info->name,
		cpt);
	ft_printf("by end-of-file (wanted `%s')\n", limiter);
}
