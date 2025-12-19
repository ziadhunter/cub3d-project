/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tan.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:25:46 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/19 12:18:25 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	safe_tan(double n)
{
	double	new_n;

	new_n = tan(n);
	if (fabs(new_n) < RAY_THRESHOLD)
		new_n = RAY_THRESHOLD;
	return (new_n);
}
