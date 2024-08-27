/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:28:40 by madamou           #+#    #+#             */
/*   Updated: 2024/08/27 16:45:46 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_a_separator(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

int	is_a_quotes(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	assigne_type(char *redirection, t_command_line *queue)
{
	if (!ft_strcmp(redirection, "|"))
		return (PIPE);
	if (!ft_strcmp(redirection, "||"))
		return (OR);
	if (!ft_strcmp(redirection, ">"))
		return (R_RED);
	if (!ft_strcmp(redirection, ">>"))
		return (RR_RED);
	if (!ft_strcmp(redirection, "<"))
		return (L_RED);
	if (!ft_strcmp(redirection, "<<"))
		return (LL_RED);
	if (!ft_strcmp(redirection, "&&"))
		return (AND);
	if (!ft_strcmp(redirection, ";") || !ft_strcmp(redirection, "\n"))
		return (LIST);
	queue->u_token_flag = 1;
	if (redirection[0] == '<')
		return (HU_TOKEN);
	return (U_TOKEN);
}

int	is_redirection(t_element *elem)
{
	if (elem->type == L_RED || elem->type == R_RED || elem->type == RR_RED)
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
