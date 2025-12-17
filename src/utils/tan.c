/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tan.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarouk <zfarouk@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:25:46 by zfarouk           #+#    #+#             */
/*   Updated: 2025/12/17 16:25:47 by zfarouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	safe_tan(double n)
{
	double	new_n;

	new_n = tan(n);
	if (fabs(new_n) < VERTICAL_RAY_THRESHOLD)
		new_n = VERTICAL_RAY_THRESHOLD;
	return (new_n);
}
