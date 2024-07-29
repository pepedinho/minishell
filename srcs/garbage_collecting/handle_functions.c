/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:25:05 by madamou           #+#    #+#             */
/*   Updated: 2024/07/29 15:51:11 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_unexpected_token(int j, char symbol)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	if (j == 3)
		ft_fprintf(2, "%s: syntax error near unexpected token `%c'\n",
				info->name, symbol);
	else
		ft_fprintf(2, "%s: syntax error near unexpected token `%c%c'\n",
				info->name, symbol, symbol);
	g_signal_code = 1;
	ft_free(DESTROY);
	exit(g_signal_code);
}

void	handle_malloc_error(char *message)
{
	t_info *info;

	info = info_in_static(NULL, GET);
	ft_fprintf(2, "%s: Error malloc when allocate for %s\n", info->name,
			message);
	g_signal_code = ERR_MALLOC;
	ft_free(DESTROY);
	exit(g_signal_code);
}