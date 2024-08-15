/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:37:18 by itahri            #+#    #+#             */
/*   Updated: 2024/08/15 04:23:32 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H
# define PATERN 1
# define DIRNAME 0
# include "../../includes/minishell.h"

int	expend_wcards(char *path, t_command_line *queue);
#endif // !WILDCARDS_H
