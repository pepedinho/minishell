/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:23:13 by madamou           #+#    #+#             */
/*   Updated: 2024/08/15 15:15:40 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

// Signals
void	sigaction_signals(int signal, void handler(int));
void	kill_if_sigint(void);
void	handle_signal_parent(int num);
void sigchld_handler(int sig);

#endif // !SIGNAL_H
