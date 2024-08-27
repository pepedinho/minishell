/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:54:03 by madamou           #+#    #+#             */
/*   Updated: 2024/08/27 14:48:21 by itahri           ###   ########.fr       */
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
	return (var[j++] = '=', var[j] = '\0', var);
}

char	*ft_check_if_variable_exist(char **envp, char *var, char *dest, int j)
{
	int		index;
	t_info	*info;

	info = info_in_static(NULL, GET);
	index = 0;
	if (ft_strcmp(var, "?=") == 0)
		return (ft_free(var), ft_sprintf("%s%d", dest, info->signal_code));
	else if (var[0] == '=')
		return (ft_free(var), ft_sprintf("%s$", dest, info->signal_code));
	while (envp[index])
	{
		if (ft_strncmp(var, envp[index], j) == 0)
			return (ft_free(var), ft_sprintf("%s%s", dest, &envp[index][j]));
		index++;
	}
	return (ft_free(var), dest);
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
