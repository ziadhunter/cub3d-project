/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:54:09 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 16:13:05 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	print_udec(va_list args, t_opt *opt)
{
	char			result[32];
	unsigned int	n;
	char			*s;

	n = va_arg(args, unsigned int);
	s = convert(result, opt->leading_space_sign, n, "0123456789");
	if (opt->precision[0] && opt->fill == '0')
		opt->fill = ' ';
	return (ft_putnbr(s, opt));
}

int	print_dec(va_list args, t_opt *opt)
{
	char	result[32];
	int		n;
	char	*s;
	char	leading_space;

	n = va_arg(args, int);
	if (n < 0)
		leading_space = '-';
	else
		leading_space = opt->leading_space_sign;
	if (n < 0)
		s = convert(result, leading_space, -(unsigned long)(n), "0123456789");
	else
		s = convert(result, leading_space, n, "0123456789");
	if (opt->precision[0] && opt->fill == '0')
		opt->fill = ' ';
	return (ft_putnbr(s, opt));
}

int	print_hex_cap(va_list args, t_opt *opt)
{
	char			result[32];
	unsigned int	n;
	int				count;
	char			*s;

	count = 0;
	n = va_arg(args, unsigned int);
	s = convert(result, 0, n, "0123456789ABCDEF");
	if (opt->alt && n)
	{
		*(--s) = 'X';
		*(--s) = '0';
	}
	if (opt->precision[0] && opt->fill == '0')
		opt->fill = ' ';
	count += ft_putnbr(s, opt);
	return (count);
}

int	print_hex(va_list args, t_opt *opt)
{
	char			result[32];
	unsigned int	n;
	int				count;
	char			*s;

	n = va_arg(args, unsigned int);
	s = convert(result, 0, n, "0123456789abcdef");
	count = 0;
	if (opt->alt && n)
	{
		*(--s) = 'x';
		*(--s) = '0';
	}
	if (opt->precision[0] && opt->fill == '0')
		opt->fill = ' ';
	count += ft_putnbr(s, opt);
	return (count);
}

int	print_addr(va_list args, t_opt *opt)
{
	char			result[32];
	unsigned long	n;
	char			*s;

	n = va_arg(args, unsigned long);
	opt->fill = ' ';
	if (n == 0)
		return (ft_putaddr("(nil)", opt));
	s = convert(result, 0, n, "0123456789abcdef");
	*(--s) = 'x';
	*(--s) = '0';
	return (ft_putaddr(s, opt));
}
