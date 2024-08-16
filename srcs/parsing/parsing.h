/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:26:17 by itahri            #+#    #+#             */
/*   Updated: 2024/08/16 19:14:47 by madamou          ###   ########.fr       */
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
	int						type;
	char					*content;
	int						infile;
	int *infile_tab;
	char					*env_value;
	struct s_element		*left;
	struct s_element		*right;
	char					**args;
	char					**outfile;
	int						*file_mode;
	struct s_element		*next;
	struct s_element		*before;
}							t_element;

/*
 * heredoc_flag = 1 if there is some in heredoc in command
 *                |
 *                --> 0 if ther is no heredoc in command
 */

typedef struct s_command_line
{
	int						heredoc_flag;
	int						u_token_flag;
	int						u_heredoc_token_flag;
	int						open_quotes_flag;
	int						open_parenthesis_flag;
	t_element				*first;
	t_element				*last;
	struct s_command_line	*next;
}							t_command_line;

// queue functions
t_command_line				*init_queue(void);
t_element					*add_to_queue(t_command_line *queue, char *content,
								int type);
void						free_queue(t_command_line *queue);
t_command_line				*parser(char *str, t_env *env);
void						print_queue(t_command_line *queue);
t_command_line				*queue_in_static(t_command_line *queue, int cas);
void	free_node_queue(t_element *node);


// utils
int							is_a_separator(char c);
int	assigne_type(char *redirection, t_command_line *queue);
int is_a_quotes(char c);
char *expand_if_necessary(char *str);
int	is_redirection(t_element *elem);
int is_space(char c);

// Before parsing
char	*check_if_command_line_is_good(char *str, t_command_line *queue);

#endif
