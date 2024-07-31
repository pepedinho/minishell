/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:26:17 by itahri            #+#    #+#             */
/*   Updated: 2024/07/31 19:20:08 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"
# include "../garbage_collecting/garbage_collecting.h"

# define NO_END_QUOTE 0

/*
 * type :
 * 1 = Command
 * 2 = suffix
 * 3 = redirection
 * 4 = file (go to minishell.h to see more)
 */

/*
 * path      = path to the  command to execute
 * fd        = tab of 2 fd for pipe communication betwen process
 * in_output = input or output_file
 */
typedef struct s_element
{
	int					type;
	int					relative_type;
	char				*content;
	int					fd[2];
	int					file_fd;
	char				*env_value;
	char				*path;
	char				*in_output;
	struct s_element	*next;
	struct s_element	*before;
}						t_element;

/*
 * heredoc_flag = 1 if there is some in heredoc in command
 *                |
 *                --> 0 if ther is no heredoc in command
 */

typedef struct s_command_line
{
	int					heredoc_flag;
	int					u_token_flag;
	int					u_heredoc_token_flag;
	int					open_quotes_flag;
	int					open_parenthesis_flag;
	t_element			*first;
	t_element			*last;
}						t_command_line;

// queue functions
t_command_line			*init_queue(void);
t_element				*add_to_queue(t_command_line *queue, char *content,
							int type, char *env_value);
void					free_queue(t_command_line *queue);
t_command_line			*parser(char *str, t_env *env);
void					print_queue(t_command_line *queue);
t_command_line			*queue_in_static(t_command_line *queue, int cas);

#endif
