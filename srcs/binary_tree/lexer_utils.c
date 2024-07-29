/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:02:31 by itahri            #+#    #+#             */
/*   Updated: 2024/07/29 09:56:42 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_a_redirect(int type)
{
	if (type == PIPE || type == R_RED || type == L_RED || type == AND
		|| type == OR || type == LIST || type == RR_RED || type == LL_RED)
		return (1);
	return (0);
}
