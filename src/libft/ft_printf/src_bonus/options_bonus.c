/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:31:54 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 16:31:55 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

void	init_options(t_opt *opt)
{
	opt->leading_space_sign = 0;
	opt->pad = 0;
	opt->width = 0;
	opt->alt = 0;
	opt->precision[0] = 0;
	opt->precision[1] = 0;
	opt->fill = ' ';
}

void	get_options(const char *s, int *i, t_opt *opt)
{
	init_options(opt);
	while (char_in_chaset(s[*i], "0.-+ #") || ft_isdigit(s[*i]))
	{
		if (s[*i] == ' ' && opt->leading_space_sign != '+')
			opt->leading_space_sign = ' ';
		else if (s[*i] == '0')
			opt->fill = '0';
		else if (s[*i] == '+')
			opt->leading_space_sign = '+';
		else if (s[*i] >= '0' && s[*i] <= '9')
			opt->width = ft_atoi_s(s, i);
		else if (s[*i] == '.')
		{
			(*i)++;
			opt->precision[0] = 1;
			opt->precision[1] = ft_atoi_s(s, i);
		}
		else if (s[*i] == '#')
			opt->alt = 1;
		else if (s[*i] == '-')
			opt->pad = 1;
		(*i)++;
	}
}
