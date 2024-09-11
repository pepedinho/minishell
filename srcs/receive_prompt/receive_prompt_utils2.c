/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:34:22 by itahri            #+#    #+#             */
/*   Updated: 2024/09/11 12:31:36 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	link_before_and_after(t_command_line *queue, t_element **current)
{
	if ((*current)->before)
		(*current)->before->next = (*current)->next;
	else
		queue->first = (*current)->next;
	if ((*current)->next)
		(*current)->next->before = (*current)->before;
}

void	free_current(t_element **current)
{
	t_element	*tmp;

	tmp = (*current)->next;
	ft_free(*current);
	*current = tmp;
}

t_command_line	*remove_in_queue(t_command_line *queue)
{
	t_element		*current;
	t_command_line	*tmp_queue;

	current = queue->first;
	while (current)
	{
		if (current->type != CMD && current->type != LOCAL_VAR
			&& current->type != C_BLOCK && current->type != N_CMD
			&& !is_a_operator(current->type))
			(link_before_and_after(queue, &current), free_current(&current));
		else if (current->type == LIST)
		{
			tmp_queue = init_queue();
			if (!tmp_queue)
				handle_malloc_error("queue");
			tmp_queue->first = current->next;
			queue_add_back(&queue, tmp_queue);
			current->before->next = NULL;
			free_current(&current);
		}
		else
			current = current->next;
	}
	return (queue);
}

void	tree_add_back(t_tree **tree, t_tree *new)
{
	t_tree	*buff;

	if (*tree == NULL)
		*tree = new;
	else
	{
		buff = *tree;
		while (buff->next)
			buff = buff->next;
		buff->next = new;
	}
	new->next = NULL;
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
			printf("|    |___[type] -> [%d]\n", current->type);
			if (current->type)
			{
				if (current->type == 1)
					printf("|             |____[Commands]\n");
				else if (current->type == 2)
					printf("|             |____[Suffix]\n");
				else if (current->type == H_FILE)
					printf("|             |____[Heredoc]\n");
				else if (current->type == C_BLOCK)
					printf("|             |____[Subshell]\n");
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

t_command_line	*parsing(char *command_line, t_info *info)
{
	t_command_line	*queue;

	queue = parser(command_line);
	if (!queue)
		return (NULL);
	print_queue(queue);
	if (global_check(queue, info) == 0)
		return (NULL);
	queue = change_queue(queue);
	queue = remove_in_queue(queue);
	return (queue);
}
