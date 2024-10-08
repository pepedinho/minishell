/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:58:52 by madamou           #+#    #+#             */
/*   Updated: 2024/08/30 20:48:51 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	skip_white_space(char *str, int *i);
void	ft_free_2d(char **split);
int		ft_strlen_2d(char **str);
char	**split_first_value(char *str, char sep);
void	add_string_char_2d(char ***tab, char *str);
int		ft_is_numeric(char *nb);
int		all_char_are_the_same(char *str);
void	set_pwd_and_shlvl(t_info *info);

#endif
