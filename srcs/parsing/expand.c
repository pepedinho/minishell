/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:31:48 by madamou           #+#    #+#             */
/*   Updated: 2024/08/15 04:51:39 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*if_dquote(char *str, int *i)
{
	int		j;
	char	*sub_str;
	char	*end_str;

	j = 1;
	while (str[*i + j] != '"')
		j++;
	sub_str = ft_substr(str, *i + 1, j - 1);
	if (!sub_str)
		handle_malloc_error("expand variable");
	sub_str = ft_parse_line(sub_str);
	end_str = ft_substr(str, *i + j + 1, ft_strlen(str));
	if (!end_str)
		handle_malloc_error("expand variable");
	str[*i] = '\0';
	str = ft_realloc(str, ft_strlen(sub_str) + ft_strlen(end_str));
	if (!str)
		handle_malloc_error("expand variable");
	(ft_strcat(str, sub_str), ft_strcat(str, end_str));
	*i += ft_strlen(sub_str);
	(ft_free(sub_str), ft_free(end_str));
	return (str);
}

char	*if_quote(char *str, int *i)
{
	int		j;
	char	*sub_str;
	char	*end_str;

	j = 1;
	while (str[*i + j] != '\'')
		j++;
	sub_str = ft_substr(str, *i + 1, j - 1);
	if (!sub_str)
		handle_malloc_error("expand variable");
	end_str = ft_substr(str, *i + j + 1, ft_strlen(str));
	if (!end_str)
		handle_malloc_error("expand variable");
	str[*i] = '\0';
	str = ft_realloc(str, ft_strlen(sub_str) + ft_strlen(end_str));
	if (!str)
		handle_malloc_error("expand variable");
	(ft_strcat(str, sub_str), ft_strcat(str, end_str));
	*i += ft_strlen(sub_str);
	(ft_free(sub_str), ft_free(end_str));
	return (str);
}

char	*if_normal(char *str, int *i)
{
	int		j;
	char	*sub_str;
	char	*end_str;

	j = 0;
	while (str[*i + j] && str[*i + j] != '"' && str[*i + j] != '\'')
		j++;
	sub_str = ft_substr(str, *i, j);
	if (!sub_str)
		handle_malloc_error("expand variable");
	sub_str = ft_parse_line(sub_str);
	end_str = ft_substr(str, *i + j, ft_strlen(str));
	if (!end_str)
		handle_malloc_error("expand variable");
	str[*i] = '\0';
	str = ft_realloc(str, ft_strlen(sub_str) + ft_strlen(end_str));
	if (!str)
		handle_malloc_error("expand variable");
	(ft_strcat(str, sub_str), ft_strcat(str, end_str));
	*i += ft_strlen(sub_str);
	(ft_free(sub_str), ft_free(end_str));
	return (str);
}

char	*expand_if_necessary(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			str = if_dquote(str, &i);
		else if (str[i] == '\'')
			str = if_quote(str, &i);
		else
			str = if_normal(str, &i);
	}
	return (str);
}
