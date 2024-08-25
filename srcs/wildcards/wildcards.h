/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:37:18 by itahri            #+#    #+#             */
/*   Updated: 2024/08/25 03:09:42 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H
# define PATERN 1
# define DIRNAME 0
# include "../../includes/minishell.h"
# include <dirent.h>

typedef struct s_wcards
{
	char *content;
	struct s_wcards *before;
	struct s_wcards *next;
}t_wcards;

int	expand_wcards(char *path, t_command_line *queue);
void create_node_wcards(t_wcards **wcards, char *str, int i, int j);
void skip_quote_wcards(char *str, int i, int *j);
int ft_strncmp_reverse(char *s1, char *s2, size_t len_s2);

#endif // !WILDCARDS_H
