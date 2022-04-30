/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_maze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:34:27 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 18:47:58 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	pour_floor_ceiling(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HG)
	{
		x = 0;
		while (x < WIN_WD)
		{
			if (y < WIN_HG / 2)
				my_mlx_pixel_put(vars, x, y, vars->ceiling_color);
			else
				my_mlx_pixel_put(vars, x, y, vars->floor_color);
			x++;
		}
		y++;
	}
}

static int	defin_color(t_ray *ray)
{
	double	xps;
	double	xms;
	double	yps;
	double	yms;

	xps = ray->end_x + 0.000001;
	xms = ray->end_x - 0.000001;
	yps = ray->end_y + 0.000001;
	yms = ray->end_y - 0.000001;
	if ((int)xms != (int)xps && (int)yms == (int)yps)
	{
		if (cos(ray->angle) < 0)
			return (M_EWLL_CLR);
		return (M_WWLL_CLR);
	}
	else
	{
		if (sin(ray->angle) < 0)
			return (M_NWLL_CLR);
		return (M_SWLL_CLR);
	}
	return (M_WLL_CLR);
}

static void	vert_line_put(t_vars *vars, int size_px, t_ray *ray)
{
	int		from;
	int		to;
	int		color;

	color = defin_color(ray);
	from = (WIN_HG - size_px) / 2;
	to = WIN_HG;
	if (size_px < WIN_HG)
		to = from + size_px;
	while (from < to)
	{
		if (from >= 0)
			my_mlx_pixel_put(vars, ray->num_line, from, color);
		from++;
	}
}

void	draw_wall(t_vars *vars, t_ray *ray)
{
	double	size_att;
	int		size_px;
	double	fish_cor_ang;

	fish_cor_ang = vars->ppa - ray->angle;
	if (fish_cor_ang < 0)
		fish_cor_ang += 2 * M_PI;
	if (fish_cor_ang > 2 * M_PI)
		fish_cor_ang -= 2 * M_PI;
	ray->dist *= cos(fish_cor_ang);
	size_att = 1.0 / ray->dist / vars->hg_dst_att;
	size_px = WIN_HG * size_att;
	if (US_TEXTURE)
		put_texture(vars, size_px, ray);
	else
		vert_line_put(vars, size_px, ray);
}

void	draw_maze(t_vars *vars)
{
	pour_floor_ceiling(vars);
	rays_caster(vars, "maze");
}
