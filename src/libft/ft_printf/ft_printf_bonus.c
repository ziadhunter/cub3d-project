/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:50:16 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 17:46:13 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	find_flag(va_list args, const char *s, int *i, t_func(functions)[10])
{
	t_opt	options;
	int		n;
	int		start;

	start = *i;
	(*i)++;
	get_options(s, i, &options);
	n = 0;
	while (functions[n].flag)
	{
		if (s[*i] == functions[n].flag)
		{
			return (functions[n].f(args, &options));
		}
		n++;
	}
	if (s[*i] == 0)
		return (-1);
	*i = start;
	return (print_mod(args, &options));
}

void	build_func(t_func (*functions)[10])
{
	(*functions)[0].flag = '%';
	(*functions)[1].flag = 'c';
	(*functions)[2].flag = 's';
	(*functions)[3].flag = 'i';
	(*functions)[4].flag = 'd';
	(*functions)[5].flag = 'u';
	(*functions)[6].flag = 'x';
	(*functions)[7].flag = 'X';
	(*functions)[8].flag = 'p';
	(*functions)[9].flag = 0;
	(*functions)[0].f = print_mod;
	(*functions)[1].f = print_char;
	(*functions)[2].f = print_str;
	(*functions)[3].f = print_dec;
	(*functions)[4].f = print_dec;
	(*functions)[5].f = print_udec;
	(*functions)[6].f = print_hex;
	(*functions)[7].f = print_hex_cap;
	(*functions)[8].f = print_addr;
	(*functions)[9].f = NULL;
}

int	init_printf(const char *str, va_list args, t_func(functions)[10])
{
	int	i;
	int	tmp;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
			tmp = find_flag(args, str, &i, functions);
		else
			tmp = ft_putchar(str[i]);
		if (tmp == -1)
			return (-1);
		count += tmp;
		i++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;
	t_func	functions[10];

	if (str == NULL)
		return (-1);
	va_start(args, str);
	build_func(&functions);
	count = init_printf(str, args, functions);
	va_end(args);
	return (count);
}
