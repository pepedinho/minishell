/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:04:37 by itahri            #+#    #+#             */
/*   Updated: 2024/07/29 23:19:08 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"

void	print_proto(t_tree *tree);

int	next_is_sfx(t_element *elem)
{
	if (elem && elem->type / 10 != 3)
		return (1);
	return (0);
}

t_tree	*init_tree(void)
{
	t_tree	*new;

	new = ft_malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->first = NULL;
	return (new);
}

void	assemble_in_tree(t_tree *tree, t_element *r_cmd, t_element *m_cmd)
{
	t_branch	*new;
	t_branch	*current;

	new = ft_malloc(sizeof(t_branch));
	if (!new)
		return ;
	new->l_cmd = NULL;
	new->r_cmd = r_cmd;
	new->redirect = m_cmd;
	if (!tree->first)
		tree->first = new;
	else
	{
		current = tree->first;
		while (current->l_cmd)
			current = current->l_cmd;
		current->l_cmd = new;
	}
}

void	add_first_cmd(t_tree *tree, t_element *first_cmd)
{
	t_branch	*current;

	current = tree->first;
	while (current && current->l_cmd)
		current = current->l_cmd;
	if (current)
		current->first_cmd = first_cmd;
}

t_tree	*smart_agencement(t_command_line *queue)
{
	t_element	*current;
	t_tree		*tree;
	t_element	*tmp;

	tree = init_tree();
	if (!tree)
		return (NULL);
	current = queue->last;
	while (current->before)
	{
		if (current->type == CMD || current->type == H_FILE)
			tmp = current;
		if (is_a_redirect(current->type))
		{
			if (current != queue->first)
				assemble_in_tree(tree, tmp, current);
			else
				assemble_in_tree(tree, current->next->next, current);
			while (current->before && current->type == SFX)
				current = current->before;
		}
		current = current->before;
	}
	add_first_cmd(tree, current);
	print_proto(tree);
	return (tree);
}

void	print_proto(t_tree *tree)
{
	t_branch	*current;
	t_element	*current_rgt;
	t_element	*first_cmd;

	current = tree->first;
	while (current)
	{
		printf("                     [%s]                    \n",
			current->redirect->content);
		printf("                    /    \\                  \n");
		printf("                   /      \\                 \n");
		printf("                 [");
		if (!current->l_cmd)
		{
			first_cmd = current->first_cmd;
			while (next_is_sfx(first_cmd))
			{
				printf("%s ", first_cmd->content);
				first_cmd = first_cmd->next;
			}
		}
		else
			printf("*");
		printf("]     [");
		current_rgt = current->r_cmd;
		while (next_is_sfx(current_rgt))
		{
			printf("%s ", current_rgt->content);
			current_rgt = current_rgt->next;
		}
		printf("]\n");
		if (current->l_cmd)
		{
			printf("                   \\\n");
			printf("                    \\\n");
		}
		current = current->l_cmd;
	}
}
