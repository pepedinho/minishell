/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:03:40 by madamou           #+#    #+#             */
/*   Updated: 2024/08/11 17:00:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_str_to_print(char *print, char c)
{
	char	*tmp;
	int		i;

	i = ft_len_print(2);
	tmp = ft_malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (ft_free(print), NULL);
	tmp[0] = '\0';
	tmp = ft_strcpyy(tmp, print);
	ft_free(print);
	print = ft_malloc(sizeof(char) * (i + 1 + 1));
	if (!print)
		return (ft_free(print), NULL);
	print = ft_strcpyy(print, tmp);
	print[i] = c;
	ft_len_print(1);
	print[++i] = '\0';
	return (ft_free(print), print);
}

char	*ft_char(char *print, char c)
{
	int	i;

	i = ft_len_print(2);
	print = ft_reallocc(print, 3);
	if (!print)
		return (NULL);
	print[i] = c;
	ft_len_print(1);
	print[++i] = '\0';
	return (print);
}

char	*ft_decimal(char *print, int nb, int cas)
{
	char	*result;
	int		len_result;

	result = ft_itoa(nb);
	if (!result)
		return (ft_free(print), NULL);
	len_result = ft_strlen1(result);
	if ((cas == 2 || cas == 3) && nb >= 0)
		len_result++;
	print = ft_reallocc(print, len_result);
	if (!print)
		return (ft_free(print), NULL);
	if (cas == 2 && nb >= 0)
		print = ft_strcatt(print, " ");
	if (cas == 3 && nb >= 0)
		print = ft_strcatt(print, "+");
	print = ft_strcatt(print, result);
	return (ft_free(print), print);
}
