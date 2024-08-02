/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:04:37 by itahri            #+#    #+#             */
/*   Updated: 2024/08/02 18:43:26 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"

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

t_tree	*smart_agencement(t_command_line *queue)
{
	t_element	*current;
	t_tree		*tree;

	tree = init_tree();
	if (!tree)
		return (NULL);
	first_join(tree, queue->first);
	if (tree->first->type == CMD || tree->first->type == C_BLOCK)
		return (tree);
	current = queue->first->next->next;
	while (current)
	{
		if (current->next && check_type(tree->first, current->next) == 1)
		{
			current->next->right = current->next->next;
			current = current->next;
			tree = replace_submit(tree, current);
			current = current->next;
			continue ;
		}
		if (!current->next)
			return (tree);
		if (check_type(tree->first, current->next) == 0)
		{
			tree = fill_right(tree, &current);
			continue ;
		}
	}
	return (tree);
}

// void	print_proto(t_tree *tree)
// {
// 	t_branch	*current;
// 	t_element	*current_rgt;
// 	t_element	*first_cmd;

// 	current = tree->first;
// 	while (current)
// 	{
// 		printf("                     [%s]                    \n",
// 				current->redirect->content);
// 		printf("                    /    \\                  \n");
// 		printf("                   /      \\                 \n");
// 		printf("                 [");
// 		if (!current->l_cmd)
// 		{
// 			first_cmd = current->first_cmd;
// 			if (first_cmd->type == C_BLOCK)
// 				printf("(%s)", first_cmd->content);
// 			while (first_cmd->type != C_BLOCK && next_is_sfx(first_cmd))
// 			{
// 				printf("%s ", first_cmd->content);
// 				first_cmd = first_cmd->next;
// 			}
// 		}
// 		else
// 			printf("*");
// 		printf("]     [");
// 		current_rgt = current->r_cmd;
// 		if (current_rgt && current_rgt->type == C_BLOCK)
// 			printf("(%s)", current_rgt->content);
// 		while (current_rgt && current_rgt->type != C_BLOCK
// 			&& next_is_sfx(current_rgt))
// 		{
// 			printf("%s ", current_rgt->content);
// 			current_rgt = current_rgt->next;
// 		}
// 		printf("]\n");
// 		if (current->l_cmd)
// 		{
// 			printf("                   \\\n");
// 			printf("                    \\\n");
// 		}
// 		current = current->l_cmd;
// 	}
// }
