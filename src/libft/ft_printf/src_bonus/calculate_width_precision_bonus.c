/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_width_precision.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:32:57 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 16:32:58 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

void	calculate_width_precision(char *s, t_opt *opt, int *slen, int *sign)
{
	if (opt->precision[0] && opt->precision[1] == 0 && s[0] == '0')
		*slen = 0;
	if (char_in_chaset(*s, "-+ "))
	{
		*sign = 1;
		(*slen)--;
	}
	if (opt->precision[1] >= *slen)
		opt->width -= opt->precision[1] + *sign;
	else
		opt->width -= *slen + *sign;
	if (opt->width < 0)
		opt->width = 0;
}
