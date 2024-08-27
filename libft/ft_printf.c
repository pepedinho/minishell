/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:12:36 by madamou           #+#    #+#             */
/*   Updated: 2024/08/27 17:32:46 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_print(int cas)
{
	static int	len;

	if (cas == 0)
		return (len = 0, len);
	if (cas == 1)
	{
		len++;
		return (len);
	}
	return (len);
}

char	*ft_printf_bis(char *print, const char *str, va_list args)
{
	int	i;

	i = 0;
	while (str[i] && print)
	{
		if (ft_check_basic(str, i) == 1)
		{
			print = ft_check_if_format(str, i, print, args);
			i += 2;
		}
		else if (str[i])
			print = ft_char(print, str[i++]);
		if (!print)
			return (NULL);
	}
	print[ft_len_print(2)] = '\0';
	return (print);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	char	*print;

	if (!str)
		return (-1);
	print = ft_malloc(sizeof(char));
	if (!print)
		return (-1);
	print[0] = '\0';
	ft_len_print(0);
	va_start(args, str);
	print = ft_printf_bis(print, str, args);
	if (!print)
		return (-1);
	return (va_end(args), ft_putstrr(print), ft_len_print(2));
}

char	*ft_sprintf(const char *str, ...)
{
	va_list	args;
	char	*print;

	if (!str)
		return (NULL);
	print = ft_malloc(sizeof(char));
	if (!print)
		return (NULL);
	print[0] = '\0';
	ft_len_print(0);
	va_start(args, str);
	print = ft_printf_bis(print, str, args);
	if (!print)
		handle_malloc_error("sprintf");
	return (va_end(args), print);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	args;
	char	*print;

	if (!str)
		return (-1);
	print = ft_malloc(sizeof(char));
	if (!print)
		return (-1);
	print[0] = '\0';
	ft_len_print(0);
	va_start(args, str);
	print = ft_printf_bis(print, str, args);
	if (!print)
		return (-1);
	ft_putstr_fd(print, fd);
	return (va_end(args), ft_len_print(2));
}
