/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:29:30 by rabounou          #+#    #+#             */
/*   Updated: 2024/12/03 16:29:44 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	writer(int *count, char *s, int slen)
{
	int	i;

	i = write(1, s, slen);
	if (i == -1)
		return (-1);
	*count += i;
	return (1);
}
