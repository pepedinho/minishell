/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:37:18 by itahri            #+#    #+#             */
/*   Updated: 2024/08/24 12:42:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H
# define PATERN 1
# define DIRNAME 0
# include "../../includes/minishell.h"
# include <dirent.h>

int	expend_wcards(char *path, t_command_line *queue);
#endif // !WILDCARDS_H
