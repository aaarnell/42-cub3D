/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 10:30:41 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/16 20:59:00 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void pour_elem_minimap(t_vars *vars, float x, float y, int clr)
{
	int i;
	int j;

	x *= MAP_Z;
	y *= MAP_Z;
	i = 0;
	while (i < MAP_Z)
	{
		j = 0;
		while (j < MAP_Z)
		{
			my_mlx_pixel_put(vars, x+j, y+i, clr);
			j++;
		}
		i++;
	}
}

static void player_output(t_vars *vars)
{
	pour_elem_minimap(vars, (vars->ppx - 0.5), (vars->ppy - 0.5), M_PLR_CLR);
}

void map_output(t_vars *vars)
{
	int	x;
	int y;
	int color;
	int len;

	y = 0;
	while (vars->map_mx[y])
	{
		x = 0;
		len = ft_strlen(vars->map_mx[y]);
		while (x < vars->w_map)
		{
			color = M_EMP_CLR;
			if (x < len && vars->map_mx[y][x] == '1')
				color = M_WLL_CLR;
			pour_elem_minimap(vars, x, y, color);
			x++;
		}
		y++;
	}
	player_output(vars);
}
