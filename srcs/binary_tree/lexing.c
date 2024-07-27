/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:04:37 by itahri            #+#    #+#             */
/*   Updated: 2024/07/27 19:49:39 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tree	*init_tree(void)
{
	t_tree	*new;

	new = ft_malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->first = NULL;
	return (new);
}

void	assemble_in_tree(t_tree *tree, t_element *r_cmd, t_element *l_cmd,
		t_element *m_cmd)
{
	t_branch	*new;
	t_branch	*current;

	new = ft_malloc(sizeof(t_branch));
	if (!new)
		return ;
	new->next = NULL;
	new->l_cmd = l_cmd;
	new->r_cmd = r_cmd;
	new->main_cmd = m_cmd;
	if (!tree->first)
		tree->first = new;
	else
	{
		current = tree->first;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_tree	*smart_agencement(t_command_line *queue)
{
	t_element	*current;
	t_element	*before;
	t_element	*tmp;
	t_tree		*tree;
	int			i;

	tree = init_tree();
	if (!tree)
		return (NULL);
	current = queue->first;
	while (current)
	{
		if (current->type / 10 == 3)
		{
			i = 0;
			if (current != queue->first)
			{
				assemble_in_tree(tree, current->next, current->before, current);
				i = 1;
			}
			else
			{
				assemble_in_tree(tree, current->next, current->next->next,
					current);
				i = 2;
			}
			while (i-- && current)
			{
				current = current->next;
			}
		}
	}
	print_tree(tree);
	return (tree);
}

void	print_tree(t_tree *tree)
{
	t_branch	*current;

	current = tree->first;
	while (current)
	{
		printf("                     [%s]                    \n",
			current->main_cmd->content);
		printf("                    /    \\                  \n");
		printf("                   /      \\                 \n");
		printf("                [%s]      [%s]", current->l_cmd->content,
			current->r_cmd->content);
		current = current->next;
	}
}
