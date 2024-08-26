/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:26:16 by madamou           #+#    #+#             */
/*   Updated: 2024/08/26 22:10:20 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*quote_or_dquote(char *str, char *prompt, t_info *info)
{
	char	*new_line;

	new_line = readline(prompt);
	if (!new_line)
	{
		if (ft_strcmp(prompt, "quote> ") == 0)
			ft_putendl_fd("minishell: unexpected EOF while looking for matching `''",
							2);
		else
			ft_putendl_fd("minishell: unexpected EOF while looking for matching `\"'",
							2);
		ft_putendl_fd("minshell: syntax error: unexpected end of file", 2);
		return (info->signal_code = 2, NULL);
	}
	str = ft_realloc(str, ft_strlen(new_line) + 1);
	if (!str)
		handle_malloc_error(prompt);
	ft_strcat(str, "\n");
	ft_strcat(str, new_line);
	free(new_line);
	return (str);
}

char	*check_if_dquote_close(char *str, int *i, t_info *info)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] == '\0')
	{
		str = quote_or_dquote(str, "dquote> ", info);
		*i = 0;
	}
	return (str);
}

char	*check_if_quote_close(char *str, int *i, t_info *info)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\0')
	{
		str = quote_or_dquote(str, "quote> ", info);
		*i = 0;
	}
	return (str);
}

int	check_if_paranthesis_close(char *str, int i)
{
	int	open_parenthesis;
	int	close_parenthesis;

	open_parenthesis = 0;
	close_parenthesis = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '(')
			open_parenthesis++;
		if (str[i] == ')')
			close_parenthesis++;
	}
	return (open_parenthesis - close_parenthesis);
}

char	*check_if_command_line_is_good(char *str, t_command_line *queue)
{
	int		i;
	t_info	*info;

	i = 0;
	info = info_in_static(NULL, GET);
	while (g_signal == 0 && str && str[i])
	{
		if (g_signal == 0 && str && str[i] == '"')
			str = check_if_dquote_close(str, &i, info);
		if (g_signal == 0 && str && str[i] == '\'')
			str = check_if_quote_close(str, &i, info);
		i++;
	}
	if (!str)
		return (NULL);
	if (g_signal != 0)
		return (set_info_if_signal(info), NULL);
	i = check_if_paranthesis_close(str, -1);
	if (i > 0)
		queue->open_parenthesis_flag = 1;
	if (i < 0)
		queue->open_parenthesis_flag = 2;
	return (str);
}
