/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:01:48 by itahri            #+#    #+#             */
/*   Updated: 2024/07/23 15:51:42 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collecting.h"

void	*ft_malloc(size_t t)
{
	static int			i;
	static t_garbage	*garbage;
	void				*ptr;

	if (!garbage)
		garbage = init_garbage();
	ptr = malloc(t);
	if (!ptr)
		return (NULL);
	push_to_garbage(garbage, ptr);
	if (!i)
		ft_free(garbage);
	i++;
	return (ptr);
}

void	ft_free(void *ptr)
{
	static int			i = -1;
	static t_garbage	*garbage;

	if (ptr == DESTROY)
	{
		destroy_all(garbage);
		return ;
	}
	if (!ptr)
		return ;
	if (i == -1)
	{
		garbage = ptr;
		i++;
		return ;
	}
	destroy(garbage, ptr);
}
