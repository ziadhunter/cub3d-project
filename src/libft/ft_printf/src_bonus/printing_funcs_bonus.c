/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:29:58 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 16:29:59 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	print_filler(int *count, char c, int cond, int n)
{
	if (cond == 0)
		return (0);
	while (n > 0)
	{
		if (writer(count, &c, 1) == -1)
			return (-1);
		n--;
	}
	return (*count);
}

int	print_precision(int *count, int precision)
{
	while (precision > 0)
	{
		if (writer(count, "0", 1) == -1)
			return (-1);
		precision--;
	}
	return (*count);
}

int	ft_putaddr(char *s, t_opt *opt)
{
	int		slen;
	int		count;
	char	*new_s;

	if (s == NULL)
		new_s = "(null)";
	else
		new_s = s;
	slen = ft_strlen(new_s);
	count = 0;
	if (print_all(&count, opt, new_s, slen) == -1)
		return (-1);
	return (count);
}

int	ft_putstr(char *s, t_opt *opt)
{
	int		slen;
	int		count;
	char	*new_s;

	if (s == NULL)
	{
		if (opt->precision[0] == 0 || (opt->precision[0]
				&& opt->precision[1] > 5))
			new_s = "(null)";
		else
			new_s = "";
	}
	else
		new_s = s;
	slen = ft_strlen(new_s);
	if (opt->precision[0] && opt->precision[1] < slen)
		slen = opt->precision[1];
	count = 0;
	if (print_all(&count, opt, new_s, slen) == -1)
		return (-1);
	return (count);
}

int	ft_putnbr(char *s, t_opt *opt)
{
	int		slen;
	char	*new_s;
	int		sign;

	if (s == NULL)
		new_s = "(null)";
	else
		new_s = s;
	slen = ft_strlen(new_s);
	sign = 0;
	calculate_width_precision(new_s, opt, &slen, &sign);
	return (print_all_2(opt, new_s, slen, sign));
}
