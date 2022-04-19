/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_maze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:34:27 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/19 23:38:13 by aarnell          ###   ########.fr       */
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
				my_mlx_pixel_put(vars, x, y, vars->ceiling_color);
			else
				my_mlx_pixel_put(vars, x, y, vars->floor_color);
			x++;
		}
		y++;
	}
}

void draw_wall(t_vars *vars, float angle)
{
	float	i;
	float	y;
	float	x;
	float	size_att;
	int		size_px;

	i = 0.1;
	while (i <= vars->len_ray)
	{
		y = vars->ppy + i * sinf(angle);
		x = vars->ppx + i * cosf(angle);
		if (vars->map_mx[(int)y][(int)x] == '1')
			break ;
		i += 0.1;
	}
	i -= 0.1;
	size_att = 1.0 / i / vars->hg_dst_att;
	size_px = WIN_HG * size_att;
	vert_line_put
}

void draw_maze(t_vars *vars)
{
	pour_floor_ceiling(vars);
	rays_caster(vars, "maze");
}
