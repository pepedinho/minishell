/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:02:19 by madamou           #+#    #+#             */
/*   Updated: 2024/07/27 19:09:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

typedef struct s_info
{
	char	*name;
	char	*path;
	char	**envp;
}			t_info;

// Prompt
void		receive_prompt(t_info *info);
void		receive_prompt_subminishell(char *command_line, t_info *info);

#endif
