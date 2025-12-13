/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:32:19 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 16:34:04 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	print_char(va_list args, t_opt *opt)
{
	int	c;
	int	count;

	count = 0;
	c = va_arg(args, int);
	if (print_filler(&count, ' ', opt->pad == 0, opt->width - 1) == -1)
		return (-1);
	if (ft_putchar(c) == -1)
		return (-1);
	count++;
	if (print_filler(&count, ' ', opt->pad == 1, opt->width - 1) == -1)
		return (-1);
	return (count);
}

int	print_str(va_list args, t_opt *opt)
{
	char	*s;

	s = va_arg(args, char *);
	opt->fill = ' ';
	return (ft_putstr(s, opt));
}

int	print_mod(va_list args, t_opt *opt)
{
	(void)opt;
	(void)args;
	return (ft_putchar('%'));
}
