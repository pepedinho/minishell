/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:54:03 by madamou           #+#    #+#             */
/*   Updated: 2024/08/18 22:25:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_normal_format(char *line, char *dest, int *i)
{
	int	len;

	len = ft_strlen(dest);
	dest = ft_realloc(dest, 2);
	if (!dest)
		return (NULL);
	while (line[*i] && line[*i] != '$')
	{
		dest = ft_realloc(dest, 2);
		if (!dest)
			return (NULL);
		dest[len++] = line[*i];
		dest[len] = '\0';
		(*i)++;
	}
	return (dest);
}

int	is_a_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_create_variable(char *line, int *i)
{
	int		j;
	char	*var;

	j = 0;
	if (line[*i] == '?')
		j = 1;
	else if (line[*i] == '{')
	{
		(*i)++;
		while (line[*i + j] != '}')
			j++;
	}
	else
	{
		while (line[*i + j] && is_a_var_char(line[*i + j]))
			j++;
	}
	var = ft_malloc(sizeof(char) * (j + 2));
	if (!var)
		return (NULL);
	var = ft_strncpy(var, &line[*i], j);
	if (line[*i + j] == '}')
		(*i)++;
	*i += j;
	var[j++] = '=';
	var[j] = '\0';
	return (var);
}

char	*ft_check_if_variable_exist(char **envp, char *var, char *dest, int j)
{
	int		index;
	t_info	*info;

	info = info_in_static(NULL, GET);
	index = 0;
	if (ft_strcmp(var, "?=") == 0)
	{
		var = ft_itoa(info->signal_code);
		dest = ft_realloc(dest, ft_strlen(var));
		if (!dest)
			return (ft_free(var), NULL);
		return (ft_strcat(dest, var), ft_free(var), dest);
	}
	else if (var[0] == '=')
	{
		dest = ft_realloc(dest, 2);
		if (!dest)
			return (ft_free(var), NULL);
		return (ft_strcat(dest, "$"), ft_free(var), dest);
	}
	while (envp[index])
	{
		if (ft_strncmp(var, envp[index], j) == 0)
		{
			dest = ft_realloc(dest, ft_strlen(&envp[index][j]));
			if (!dest)
				return (ft_free(var), NULL);
			return (ft_strcat(dest, &envp[index][j]), ft_free(var), dest);
		}
		index++;
	}
	dest = ft_realloc(dest, 1);
	if (!dest)
		return (ft_free(var), NULL);
	return (dest = ft_strcat(dest, "\0"), ft_free(var), dest);
}

char	*ft_is_evn_variable(char *line, char **envp)
{
	char	*dest;
	char	*var;
	int		i;

	i = 0;
	dest = NULL;
	while (line[i])
	{
		dest = ft_normal_format(line, dest, &i);
		if (dest == NULL)
			return (NULL);
		if (!line[i])
			return (dest);
		if (line[i] == '$')
			i++;
		var = ft_create_variable(line, &i);
		if (!var)
			return (ft_free(dest), NULL);
		dest = ft_check_if_variable_exist(envp, var, dest, ft_strlen(var));
		if (!dest)
			return (NULL);
	}
	return (dest);
}

char	*ft_parse_line(char *line)
{
	char	*dest;
	char	**envp;
	t_info	*info;

	info = info_in_static(NULL, GET);
	dest = ft_strchr(line, '$');
	if (!dest)
		return (line);
	envp = t_env_to_envp(info->env, ALL);
	if (!envp)
		handle_malloc_error("heredoc");
	dest = ft_is_evn_variable(line, envp);
	ft_free_2d(envp);
	if (!dest)
		handle_malloc_error("heredoc");
	return (ft_free(line), dest);
}
