/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:25:05 by madamou           #+#    #+#             */
/*   Updated: 2024/07/29 09:29:26 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_unexpected_token(int j, char symbol)
{
	if (j == 3)
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n",
				symbol);
	else
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c%c'\n",
				symbol, symbol);
	g_signal_code = 1;
	free_and_exit();
}

void	handle_malloc_error(char *message)
{
	ft_fprintf(2, "Error malloc when allocate for %s\n", message);
	g_signal_code = ERR_MALLOC;
	free_and_exit();
}