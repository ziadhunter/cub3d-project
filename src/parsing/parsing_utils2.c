/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:52:37 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/19 11:52:38 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_space_or_wall(char c)
{
	if (c == ' ' || c == '1' || c == '\0')
		return (1);
	return (0);
}

bool	result_out_of_range(int result)
{
	return (result < 0 || result > 255);
}

int	is_map_element(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == 'D')
		return (1);
	return (0);
}
