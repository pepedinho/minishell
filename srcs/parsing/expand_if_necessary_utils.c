/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_if_necessary_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:47:45 by madamou           #+#    #+#             */
/*   Updated: 2024/08/27 23:49:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*normal_or_dollar(char *str, int *i, int j)
{
	char	*sub_str;
	char	*end_str;

	sub_str = ft_substr(str, *i, j);
	if (!sub_str)
		handle_malloc_error("expand variable");
	sub_str = ft_parse_line(sub_str);
	end_str = ft_substr(str, *i + j, ft_strlen(str));
	if (!end_str)
		handle_malloc_error("expand variable");
	str[*i] = '\0';
	str = ft_realloc(str, ft_strlen(sub_str) + ft_strlen(end_str) + 1);
	if (!str)
		handle_malloc_error("expand variable");
	(ft_strcat(str, sub_str), ft_strcat(str, end_str));
	*i += ft_strlen(sub_str);
	(ft_free(sub_str), ft_free(end_str));
	return (str);
}

char	*if_dollar(char *str, int *i)
{
	char	*end_str;
	int		j;

	j = 0;
	if (str[*i + 1] == '"' || str[*i + 1] == '\'')
	{
		end_str = ft_strdup(&str[*i] + 1);
		str[*i] = '\0';
		if (str[*i + 1] == '"')
			end_str = if_dquote(end_str, &j);
		else
			end_str = if_quote(end_str, &j);
		*i += j;
		str = ft_realloc(str, ft_strlen(end_str));
		ft_strcat(str, end_str);
		return (str);
	}
	if (str[*i + 1] == '{')
		return (if_cursh(str, i));
	else
		str = if_normal(str, i);
	return (str);
}
