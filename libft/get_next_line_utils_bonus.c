/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:39:33 by itahri            #+#    #+#             */
/*   Updated: 2024/06/28 20:39:15 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <string.h>

int	ft_strlen_gnl(char *str, int cas)
{
	int	i;

	i = 0;
	if (cas == 1)
	{
		while (str && str[i])
			i++;
	}
	if (cas == 2)
	{
		while (str && str[i] != '\n')
			i++;
		i++;
	}
	return (i);
}

char	*ft_strcpy(char *dest, char *src)
{
	size_t	*intdest;
	size_t	*intsrc;
	size_t	len_int;
	size_t	i;

	intdest = (size_t *)dest;
	intsrc = (size_t *)src;
	len_int = ft_strlen_gnl(src, 1) / sizeof(size_t);
	i = 0;
	while (i < len_int)
	{
		intdest[i] = intsrc[i];
		i++;
	}
	i *= sizeof(size_t);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest[i] = '\0', dest);
}

int	ft_check_if_newline(char *sortie)
{
	int	i;

	i = 0;
	if (!sortie)
		return (0);
	while (sortie[i])
	{
		if (sortie[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_format_sortie(char *sortie)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	i = ft_strlen_gnl(sortie, 2);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (free(sortie), NULL);
	while (j < i)
	{
		str[j] = sortie[j];
		++j;
	}
	str[j] = '\0';
	free(sortie);
	return (str);
}
