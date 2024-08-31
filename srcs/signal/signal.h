/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:23:13 by madamou           #+#    #+#             */
/*   Updated: 2024/08/31 15:08:12 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

// Signals
void	handle_signal_parent(int num);
void	set_signal_parent(void);
void	set_signal_child(void);
void	set_signal_parent_exec(void);
void	check_if_signal(t_info *info);
int		sig_event(void);
void	if_sigint(int sig);
void	set_info_if_signal(t_info *info);

#endif // !SIGNAL_H
