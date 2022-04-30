/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_caster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:45:24 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 20:00:34 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static double	round_coord(double cossin, double crd)
{
	double	res_crd;

	res_crd = crd;
	if (cossin < 0)
	{
		res_crd = floor(crd);
		if (res_crd == crd)
			res_crd -= 1.0;
	}
	else if (cossin > 0)
	{
		res_crd = ceil(crd);
		if (res_crd == crd)
			res_crd += 1.0;
	}
	return (res_crd);
}

static void	def_next_intersect(t_vars *vars, t_ray *ray)
{
	double	hpx;
	double	hpy;
	double	tx;
	double	ty;

	tx = round_coord(cos(ray->angle), ray->end_x);
	ty = round_coord(sin(ray->angle), ray->end_y);
	hpx = 0;
	hpy = 0;
	if (cos(ray->angle))
		hpx = fabs((vars->ppx - tx) / cos(ray->angle));
	if (sin(ray->angle))
		hpy = fabs((vars->ppy - ty) / sin(ray->angle));
	if (hpx == 0 || (hpy != 0 && hpy <= hpx))
	{
		ray->end_x = vars->ppx + hpy * cos(ray->angle);
		ray->end_y = ty;
		ray->dist = hpy;
		return ;
	}
	ray->end_x = tx;
	ray->end_y = vars->ppy + hpx * sin(ray->angle);
	ray->dist = hpx;
}

static int	chk_stop(char **map, double x, double y)
{
	if (map[(int)y][(int)x] == '1' ||
		map[(int)(y - 0.00001)][(int)x] == '1' ||
		map[(int)y][(int)(x - 0.00001)] == '1')
		return (1);
	return (0);
}

static void	ray_cast(t_vars *vars, t_ray *ray)
{
	ray->dist = 0.0;
	ray->end_x = vars->ppx;
	ray->end_y = vars->ppy;
	while (ray->dist <= (double)vars->len_ray)
	{
		def_next_intersect(vars, ray);
		if (chk_stop(vars->map_mx, ray->end_x, ray->end_y))
			break ;
	}
}

void	rays_caster(t_vars *vars, char *ray_maze)
{
	double	st;
	int		sgn;
	t_ray	ray;

	sgn = 0;
	ray.num_line = 0;
	if (!ft_strncmp(ray_maze, "rays", 4))
		sgn = 1;
	if (!ft_strncmp(ray_maze, "maze", 4))
		sgn = 2;
	if (!sgn)
		return ;
	st = vars->hlf_vw_angle * 2 / WIN_WD;
	ray.angle = vars->ppa - vars->hlf_vw_angle;
	while (ray.angle < vars->ppa + vars->hlf_vw_angle)
	{
		ray_cast(vars, &ray);
		if (sgn == 1)
			draw_ray(vars, &ray);
		if (sgn == 2)
			draw_wall(vars, &ray);
		ray.angle += st;
		ray.num_line++;
	}
}
