/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:17:37 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 16:54:28 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../includes/minishell.h"

int		ft_cd(char *directory);
void	ft_echo(char *command, int flag);
void	env(void);
void	print_env(t_env *env, int cas);

#endif // !BUILTINS_H
