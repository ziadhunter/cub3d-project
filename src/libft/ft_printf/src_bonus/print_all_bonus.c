/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:32:06 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 16:33:49 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	print_all(int *count, t_opt *opt, char *s, int slen)
{
	if (print_filler(count, opt->fill, opt->pad == 0, opt->width - slen) == -1)
		return (-1);
	if (writer(count, s, slen) == -1)
		return (-1);
	if (print_filler(count, opt->fill, opt->pad == 1, opt->width - slen) == -1)
		return (-1);
	return (*count);
}

int	print_all_2(t_opt *opt, char *s, int slen, int sign)
{
	int	count;

	count = 0;
	if (sign && opt->fill == '0')
		count += ft_putchar(*s++);
	if (print_filler(&count, opt->fill, opt->pad == 0, opt->width) == -1)
		return (-1);
	if (sign && opt->fill == ' ')
		count += ft_putchar(*s++);
	if (print_precision(&count, opt->precision[1] - slen) == -1)
		return (-1);
	if (writer(&count, s, slen) == -1)
		return (-1);
	if (print_filler(&count, opt->fill, opt->pad == 1, opt->width) == -1)
		return (-1);
	return (count);
}
