/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:39:15 by madamou           #+#    #+#             */
/*   Updated: 2024/09/02 10:54:00 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_prompt(t_info *info)
{
	char	*pwd;
	char	*hostname;
	char	*prompt;

	if (info->env && ft_getenv("PWD") && ft_getenv("USER"))
	{
		pwd = ft_getenv("PWD");
		hostname = ft_getenv("USER");
		if (info->signal_code == 0)
			prompt = ft_sprintf("%s%s:\001\033[0;32m\002%s\001\033[0m\002$ ",
					CLR, hostname, pwd);
		else
			prompt = ft_sprintf("%s%s:\001\033[0;32m\002%s\001\033%s ", CLR,
					hostname, pwd, ND);
		return (prompt);
	}
	return (ft_sprintf("minishell> "));
}

char	**prepare_args_to_exec(t_element *cmd)
{
	char		**cmd_tab;
	t_element	*current;
	int			i;

	i = 0;
	current = cmd;
	while (current && !is_a_operator(current->type))
	{
		i++;
		current = current->next;
	}
	current = cmd;
	cmd_tab = ft_malloc(sizeof(char *) * (i + 1));
	if (!cmd_tab)
		handle_malloc_error("parsing");
	i = 0;
	while (current && !is_a_operator(current->type))
	{
		if (current->type == SFX || current->type == CMD
			|| current->type == C_BLOCK || current->type == LOCAL_VAR)
			cmd_tab[i++] = current->content;
		current = current->next;
	}
	return (cmd_tab[i] = NULL, cmd_tab);
}

void	add_string_char_2d(char ***tab, char *str)
{
	char	**new;
	int		i;
	char	**buff;

	buff = *tab;
	new = ft_malloc(sizeof(char *) * (ft_strlen_2d(buff) + 1 + 1));
	if (!new)
		handle_malloc_error("pasing");
	i = 0;
	while (buff && buff[i])
	{
		new[i] = buff[i];
		if (!new[i])
			handle_malloc_error("parsing");
		i++;
	}
	new[i] = str;
	if (!new[i])
		handle_malloc_error("parsing");
	new[++i] = NULL;
	ft_free(buff);
	*tab = new;
}

void	add_int_to_tab(int **tab, int nb, char **char_tab)
{
	int	*new;
	int	i;
	int	*buff;

	buff = *tab;
	new = ft_malloc(sizeof(int) * (ft_strlen_2d(char_tab) + 1));
	if (!new)
		handle_malloc_error("pasing");
	i = 0;
	while (char_tab && char_tab[i])
	{
		new[i] = buff[i];
		i++;
	}
	new[i] = nb;
	ft_free(buff);
	*tab = new;
}

void	stock_infile_outfile(t_change *change, t_element **node)
{
	t_element	*current;

	current = *node;
	if (current->type == RR_RED || current->type == R_RED)
	{
		add_int_to_tab(&change->file_mode, current->type, change->output);
		add_string_char_2d(&change->output, current->next->content);
	}
	else if (current->type == L_RED || current->type == LL_RED)
	{
		add_int_to_tab(&change->infile_tab, current->next->fd, change->infile);
		add_string_char_2d(&change->infile, current->next->content);
	}
	current = current->next;
	*node = current;
}
