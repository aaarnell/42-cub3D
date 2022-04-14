/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:17:22 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/14 21:47:13 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void pour_floor_ceiling(t_vars *vars)
{
	int	x;
	int y;

	y = 0;
	while (y < vars->hg)
	{
		x = 0;
		while (x < vars->wd)
		{
			if (y < vars->hg / 2)
				mlx_pixel_put(vars->mlx, vars->win, x, y, vars->ceiling_color);
			else
				mlx_pixel_put(vars->mlx, vars->win, x, y, vars->floor_color);
			x++;
		}
		y++;
	}
}


int	render_frame(t_vars *vars)
{
	pour_floor_ceiling(vars);
	return (0);
}
