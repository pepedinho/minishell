/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:50:12 by itahri            #+#    #+#             */
/*   Updated: 2024/08/28 00:07:46 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parsing.h"

int	add_elem_for_parenthesis(t_command_line *queue, char *str, int *i)
{
	int	j;
	int	open_parenthesis;
	int	close_parenthesis;

	j = 0;
	open_parenthesis = 1;
	close_parenthesis = 0;
	while (str[*i + ++j])
	{
		if (str[*i + j] == '(')
			open_parenthesis++;
		if (str[*i + j] == '"')
			continue_until_find(i, &j, str, '"');
		if (str[*i + j] == '\'')
			continue_until_find(i, &j, str, '\'');
		if (str[*i + j] == ')')
			close_parenthesis++;
		if (open_parenthesis - close_parenthesis == 0)
			break ;
	}
	if (!str[*i + j] && open_parenthesis - close_parenthesis != 0)
		return (queue->open_parenthesis_flag = 1, *i += j, NO_END_QUOTE);
	return (add_prth_ext(queue, str, i, j));
}

char	*add_elem(t_command_line *queue, char *str, int *i)
{
	if (str[*i] == '(')
		add_elem_for_parenthesis(queue, str, i);
	else if (is_a_separator(str[*i]))
		add_redirect(queue, str, i);
	else
		add_command(queue, str, i);
	return (str);
}

t_command_line	*parser(char *str, t_info *info)
{
	int				i;
	t_command_line	*queue;
	char			*tmp;

	if (!str[0])
		return (NULL);
	queue = init_queue();
	tmp = ft_strdup(str);
	i = 0;
	str = check_if_command_line_is_good(str, queue);
	if (!str)
		return (add_history(tmp), NULL);
	ft_free(tmp);
	add_history(str);
	while (str[i])
	{
		skip_white_space(str, &i);
		if (str[i])
			str = add_elem(queue, str, &i);
	}
	info->signal_code = 0;
	return (queue);
}
