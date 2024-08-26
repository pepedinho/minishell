/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:04:37 by itahri            #+#    #+#             */
/*   Updated: 2024/08/26 22:51:04 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*init_tree(void)
{
	t_tree	*new;

	new = ft_malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->first = NULL;
	new->next = NULL;
	return (new);
}

t_tree	*replace_submit(t_tree *tree, t_element *current)
{
	t_element	*buff;

	buff = tree->first;
	tree->first = current;
	current->left = buff;
	return (tree);
}

void	finish_tree(t_tree **tree, t_element *current)
{
	while (current)
	{
		if (current->next && check_type((*tree)->first, current->next) == 1)
		{
			current->next->right = current->next->next;
			current = current->next;
			*tree = replace_submit(*tree, current);
			current = current->next;
			continue ;
		}
		if (!current->next)
			return ;
		if (check_type((*tree)->first, current->next) == 0)
		{
			*tree = fill_right(*tree, &current);
			continue ;
		}
	}
}

t_tree	*smart_agencement(t_command_line *queue)
{
	t_element	*current;
	t_tree		*tree;

	tree = init_tree();
	if (!tree)
		handle_malloc_error("ast");
	first_join(tree, queue->first);
	if (tree->first->type == CMD || tree->first->type == C_BLOCK
		|| tree->first->type == LOCAL_VAR || tree->first->type == N_CMD)
		return (tree);
	current = queue->first->next->next;
	finish_tree(&tree, current);
	return (tree);
}
