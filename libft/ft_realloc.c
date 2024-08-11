/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:11:50 by madamou           #+#    #+#             */
/*   Updated: 2024/08/11 16:43:59 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, int len_realloc)
{
	char	*tmp;
	int		i;

	i = ft_strlen(ptr);
	tmp = ft_malloc(sizeof(char) * (i + len_realloc + 1));
	if (!tmp)
	{
		ft_free(ptr);
		return (NULL);
	}
	tmp[0] = '\0';
	tmp = ft_strcpy(tmp, ptr);
	ft_free(ptr);
	return (tmp);
}
