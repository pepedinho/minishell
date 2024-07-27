/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:04:37 by itahri            #+#    #+#             */
/*   Updated: 2024/07/27 19:58:03 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"

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
	t_tree		*tree;
	t_element	*tmp;
	int			i;

	tree = init_tree();
	if (!tree)
		return (NULL);
	current = queue->first;
	while (current)
	{
		if (current->type == CMD)
			tmp = current;
		if (current->type / 10 == 3)
		{
			i = 0;
			if (current != queue->first)
			{
				assemble_in_tree(tree, current->next, tmp, current);
				i = 1;
			}
			else
			{
				assemble_in_tree(tree, current->next->next, tmp, current);
				i = 2;
			}
			while (i-- && current)
			{
				current = current->next;
			}
		}
		current = current->next;
	}
	return (tree);
}

void	print_tree(t_tree *tree)
{
	t_branch	*current;
	t_element	*current_lft;
	t_element	*current_rgt;

	current = tree->first;
	while (current)
	{
		printf("                     [%s]                    \n",
			current->main_cmd->content);
		printf("                    /    \\                  \n");
		printf("                   /      \\                 \n");
		printf("             [");
		current_lft = current->l_cmd;
		while (current_lft && current_lft->type / 10 != 3)
		{
			printf("%s ", current_lft->content);
			current_lft = current_lft->next;
		}
		printf("]     [");
		current_rgt = current->r_cmd;
		while (current_rgt && current_rgt->type / 10 != 3)
		{
			printf("%s ", current_rgt->content);
			current_rgt = current_rgt->next;
		}
		printf("]\n");
		current = current->next;
	}
}
