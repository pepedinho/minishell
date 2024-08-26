/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:02:31 by itahri            #+#    #+#             */
/*   Updated: 2024/08/26 22:48:54 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_join(t_tree *tree, t_element *first)
{
	if (first->next)
	{
		tree->first = first->next;
		tree->first->left = first;
		tree->first->right = first->next->next;
	}
	else
		tree->first = first;
}

int	check_type(t_element *first, t_element *current)
{
	if (current->type == CMD)
		return (0);
	if (first->type == PIPE)
		return (1);
	else
	{
		if (current->type == PIPE)
			return (0);
		else if (current->type == AND || current->type == OR)
			return (1);
	}
	return (0);
}

void	first_join_right(t_tree *tree, t_element *first)
{
	tree->first->right = first->next;
	tree->first->right->left = first;
	tree->first->right->right = first->next->next;
}

t_tree	*replace_submit_right(t_tree *tree, t_element *current)
{
	t_element	*buff;

	buff = tree->first->right;
	tree->first->right = current;
	current->left = buff;
	return (tree);
}

t_tree	*fill_right(t_tree *tree, t_element **current)
{
	first_join_right(tree, *current);
	*current = (*current)->next->next;
	while (*current && (*current)->next && check_type(tree->first,
			(*current)->next) == 0)
	{
		(*current)->next->right = (*current)->next->next;
		*current = (*current)->next;
		replace_submit_right(tree, *current);
		*current = (*current)->next;
	}
	return (tree);
}
