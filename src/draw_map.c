/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 10:30:41 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 17:08:29 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	pour_elem_minimap(t_vars *vars, double x, double y, int clr)
{
	int	i;
	int	j;

	x *= MAP_Z;
	y *= MAP_Z;
	i = 0;
	while (i < MAP_Z)
	{
		j = 0;
		while (j < MAP_Z)
		{
			my_mlx_pixel_put(vars, x + j, y + i, clr);
			j++;
		}
		i++;
	}
}

static void	player_output(t_vars *vars)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = MAP_Z * vars->ppx;
	y = MAP_Z * vars->ppy;
	i = 0 - PLR_SIZE / 2;
	while (i < (PLR_SIZE / 2 + PLR_SIZE % 2))
	{
		j = 0 - PLR_SIZE / 2;
		while (j < (PLR_SIZE / 2 + PLR_SIZE % 2))
		{
			my_mlx_pixel_put(vars, x + j, y + i, M_PLR_CLR);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_vars *vars, t_ray *ray)
{
	double	i;
	double	y;
	double	x;
	double	st;

	st = (double)1 / (double)MAP_Z;
	i = st;
	while (i < ray->dist)
	{
		y = vars->ppy + i * sin(ray->angle);
		x = vars->ppx + i * cos(ray->angle);
		my_mlx_pixel_put(vars, x * MAP_Z, y * MAP_Z, M_RAY_CLR);
		i += st;
	}
}

void	draw_map(t_vars *vars)
{
	int	x;
	int	y;
	int	color;
	int	len;

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
	rays_caster(vars, "rays");
}
