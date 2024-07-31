/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:50:12 by itahri            #+#    #+#             */
/*   Updated: 2024/07/31 19:47:13 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parsing.h"

int	is_a_separator(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&' || c == ';')
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
	if (!ft_strcmp(redirection, ";"))
		return (LIST);
	queue->u_token_flag = 1;
	if (redirection[0] == '<')
		return (HU_TOKEN);
	return (U_TOKEN);
}

int	add_redirect(t_command_line *queue, char *str, int *i)
{
	char	*redirection;
	char	symbol;
	int		type;
	int		j;

	symbol = str[*i];
	j = 0;
	while (str[*i + j] == symbol)
		j++;
	// if (j > 2)
	//	handle_unexpected_token(j, symbol, INIT);
	redirection = ft_malloc(sizeof(char) * (j + 1));
	if (!redirection)
		handle_malloc_error("redirections");
	j = -1;
	while (str[*i + ++j] == symbol)
		redirection[j] = str[*i + j];
	redirection[j] = '\0';
	type = assigne_type(redirection, queue);
	add_to_queue(queue, redirection, type, NULL);
	*i += j;
	return (1);
}

int	add_elem_for_quotes(t_command_line *queue, char *str, int *i)
{
	int		j;
	char	*cmd;

	j = 1;
	while (str[*i + j] && str[*i + j] != '"')
		j++;
	if ((!str[*i + j] && str[*i + j - 1] != '"') || (str[*i + j - 1] == '"'
			&& j == 1))
	{
		queue->open_quotes_flag = 1;
		// return (NO_END_QUOTE); // handle when quote dosen't end
	}
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		handle_malloc_error("quotes");
	j = 1;
	while (str[*i + j] && str[*i + j] != '"')
	{
		cmd[j - 1] = str[*i + j];
		j++;
	}
	cmd[j - 1] = '\0';
	if (!add_to_queue(queue, cmd, 1, NULL))
		return (g_signal_code = 105, ERR_MALLOC);
	*i += j;
	return (1);
}

int	add_command(t_command_line *queue, char *str, int *i)
{
	int		j;
	char	*cmd;

	j = 0;
	while (str[*i + j] && str[*i + j] != ' ' && !is_a_separator(str[*i + j]))
		j++;
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		handle_malloc_error("commands");
	j = 0;
	while (str[*i + j] && str[*i + j] != ' ' && !is_a_separator(str[*i + j]))
	{
		cmd[j] = str[*i + j];
		j++;
	}
	cmd[j] = '\0';
	if (!add_to_queue(queue, cmd, 1, NULL))
		handle_malloc_error("commands");
	*i += j;
	return (1);
}

int	add_elem_for_parenthesis(t_command_line *queue, char *str, int *i)
{
	int		j;
	char	*cmd;

	j = 1;
	while (str[*i + j] && str[*i + j] != ')')
		j++;
	if (!str[*i + j] && str[*i + j - 1] != ')')
	{
		queue->open_parenthesis_flag = 1;
		return (NO_END_QUOTE); // handle when quote dosen't end
	}
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		handle_malloc_error("parenthesis");
	j = 1;
	while (str[*i + j] && str[*i + j] != ')')
	{
		cmd[j - 1] = str[*i + j];
		j++;
	}
	cmd[j - 1] = '\0';
	if (!add_to_queue(queue, cmd, C_BLOCK, NULL))
		return (g_signal_code = 105, ERR_MALLOC);
	*i += j + 1;
	return (1);
}

int	add_env_var(t_command_line *queue, char *str, int *i, t_env *env)
{
	int		j;
	char	*cmd;
	t_env	*current;

	j = 1;
	while (str[*i + j] && (str[*i] != ' ' && !is_a_separator(str[*i])))
		j++;
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		handle_malloc_error("parenthesis");
	j = 1;
	while (str[*i + j] && (str[*i] != ' ' && !is_a_separator(str[*i])))
	{
		cmd[j - 1] = str[*i + j];
		j++;
	}
	cmd[j - 1] = '\0';
	current = env;
	while (current && ft_strcmp(current->key, cmd))
		current = current->next;
	if (!add_to_queue(queue, cmd, ENV, current->value))
		return (g_signal_code = 105, ERR_MALLOC);
	*i += j + 1;
	return (1);
}

int	add_elem(t_command_line *queue, char *str, int *i, t_env *env)
{
	if (str[*i] == '(')
		add_elem_for_parenthesis(queue, str, i);
	else if (str[*i] == '"')
		add_elem_for_quotes(queue, str, i);
	else if (str[*i] == '$')
		add_env_var(queue, str, i, env);
	else if (is_a_separator(str[*i]))
		add_redirect(queue, str, i);
	else
		add_command(queue, str, i);
	return (1);
}

void	skip_white_space(char *str, int *i)
{
	while (str[*i] == ' ')
		++(*i);
}

t_command_line	*parser(char *str, t_env *env)
{
	int				i;
	t_command_line	*queue;

	queue = init_queue();
	i = 0;
	while (str[i])
	{
		skip_white_space(str, &i);
		add_elem(queue, str, &i, env);
	}
	queue = queue_in_static(queue, INIT);
	return (queue);
}

void	print_queue(t_command_line *queue)
{
	t_element	*current;
	int			i;

	i = 0;
	current = queue->first;
	while (current)
	{
		if (current->type != 2)
		{
			printf("|\n");
			printf("|__[%d]\n", i);
			printf("|    |___[content] -> ['%s']\n", current->content);
			if (current->type == ENV)
				printf("|    |___[env content] -> ['%s']\n",
						current->env_value);
			printf("|    |___[type] -> [%d]\n", current->type);
			if (current->type)
			{
				if (current->type == 1)
					printf("|             |____[Commands]\n");
				else if (current->type == 2)
					printf("|             |____[Suffix]\n");
				else if (current->type == H_FILE)
					printf("|             |____[Heredoc]\n");
				else if (current->type == PIPE)
					printf("|             |____[Pipe]\n");
				else if (current->type == OR)
					printf("|             |____[Or]\n");
				else if (current->type == R_RED)
					printf("|             |____[Right Redirect]\n");
				else if (current->type == RR_RED)
					printf("|             |____[RRight Redirect]\n");
				else if (current->type == L_RED)
					printf("|             |____[Left Redirect]\n");
				else if (current->type == LL_RED)
					printf("|             |____[LLeft Redirect]\n");
				else if (current->type == AND)
					printf("|             |____[And]\n");
				else if (current->type == LIST)
					printf("|             |____[List]\n");
				else if (current->type == FILE)
					printf("|             |____[File]\n");
				else if (current->type == ENV)
					printf("|             |____[Env arg]\n");
			}
		}
		else
		{
			printf("|                |\n");
			printf("|                |__[%d]\n", i);
			printf("|                |    |___[content] -> ['%s']\n",
					current->content);
			printf("|                |    |___[type] -> [%d]\n", current->type);
			printf("|                |                    |____[Suffix]\n");
			if (current->type)
			{
			}
		}
		i++;
		current = current->next;
	}
}
