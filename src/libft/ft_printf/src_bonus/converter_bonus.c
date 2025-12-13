/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:32:37 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 16:32:38 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

char	*convert(char *result, int sign_space, unsigned long n, char *base)
{
	int	k;
	int	blen;

	blen = ft_strlen(base);
	k = 31;
	result[k--] = 0;
	if (n == 0)
		result[k--] = '0';
	while (n)
	{
		result[k--] = base[n % blen];
		n /= blen;
	}
	if (sign_space)
		result[k--] = sign_space;
	return (result + k + 1);
}
