/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 10:30:41 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/17 21:54:24 by aarnell          ###   ########.fr       */
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
	//pour_elem_minimap(vars, (vars->ppx - 0.5), (vars->ppy - 0.5), M_PLR_CLR);
	//my_mlx_pixel_put(vars, vars->ppx * MAP_Z, vars->ppy * MAP_Z, M_PLR_CLR);
	int i;
	int j;
	int x;
	int y;

	x = MAP_Z * (vars->ppx - 0.2);
	y = MAP_Z * (vars->ppy - 0.2);
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(vars, x + j, y + i, M_PLR_CLR);
			j++;
		}
		i++;
	}
}

static void ray_output(t_vars *vars, float angle)
{
	float	st;
	float	st_y;
	float	st_x;

	st = 0.1;
	while (st <= (float)vars->len_ray)
	{
		st_y = vars->ppy + st * sinf(angle);
		st_x = vars->ppx + st * cosf(angle);
		if (vars->map_mx[(int)st_y][(int)st_x] == '1')
			return ;
		my_mlx_pixel_put(vars, st_x * MAP_Z, st_y * MAP_Z, M_RAY_CLR);
		st+=0.1;
	}
}

static void rays_caster(t_vars *vars)
{
	float angle;

	angle = vars->ppa - M_PI_4;
	while (angle < vars->ppa + M_PI_4)
	{
		ray_output(vars, angle);
		angle += (M_PI / 180);
	}
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
	rays_caster(vars);
}
