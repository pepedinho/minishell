/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:04:37 by itahri            #+#    #+#             */
/*   Updated: 2024/07/28 19:33:22 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"

void	print_proto(t_tree *tree);

t_sfx	*init_sfx(void)
{
	t_sfx	*new;

	new = ft_malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->first = NULL;
	return (new);
}

void	add_sfx(t_sfx *sfx_queue, t_element *sfx)
{
	t_cmd_sfx	*new;
	t_cmd_sfx	*current;

	new = ft_malloc(sizeof(t_branch));
	if (!new)
		return ;
	new->next = NULL;
	new->suffix = sfx;
	if (!sfx_queue->first)
		sfx_queue->first = new;
	else
	{
		current = sfx_queue->first;
		while (current->next)
			current = current->next;
		current->next = new;
	}
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
	while (current->l_cmd)
		current = current->l_cmd;
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
		if (current->type == CMD)
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
			while (first_cmd && first_cmd->type / 10 != 3)
			{
				printf("%s ", first_cmd->content);
				first_cmd = first_cmd->next;
			}
		}
		else
			printf("*");
		printf("]     [");
		current_rgt = current->r_cmd;
		while (current_rgt && current_rgt->type / 10 != 3)
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
