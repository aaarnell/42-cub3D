/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_caster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:45:24 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/26 22:17:24 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static float round_coord(float cossin, float crd)
{
	float	res_crd;

	res_crd = crd;
	if (cossin < 0)
	{
		res_crd = floorf(crd);
		if (res_crd == crd)
			res_crd -= 1.0;
	}
	else if (cossin > 0)
	{
		res_crd = ceilf(crd);
		if (res_crd == crd)
			res_crd += 1.0;
	}
	return (res_crd);
}

static float def_next_intersect(float angle, float *x, float *y)
{
	float	hpX;
	float	hpY;
	float	tx;
	float	ty;

	tx = round_coord(cosf(angle), *x);
	ty = round_coord(sinf(angle), *y);
	hpX = 0;
	hpY = 0;
	if (cosf(angle))
		hpX = fabsf((*x - tx) / cosf(angle));
	if (sinf(angle))
		hpY = fabsf((*y - ty) / sinf(angle));
	if (hpX == 0 || (hpY != 0 && hpY <= hpX))
	{
		*x = *x + hpY * cosf(angle);
		*y = ty;
		return (hpY);
	}
	*x = tx;
	*y = *y + hpX * sinf(angle);
	return (hpX);
}

static void ray_cast(t_vars *vars, t_ray *ray)
{
	float	step;
	float	tx;
	float	ty;

	ray->dist = 0.0;
	tx = vars->ppx;
	ty = vars->ppy;
	while (ray->dist <= (float)vars->len_ray)
	{
		step = def_next_intersect(ray->angle, &tx, &ty);
		ray->dist += step;
		if (vars->map_mx[(int)ty][(int)tx] == '1' ||
			vars->map_mx[(int)(ty-0.01)][(int)tx] == '1' ||
			vars->map_mx[(int)ty][(int)(tx-0.01)] == '1')
			break ;
	}
	ray->end_x = tx;
	ray->end_y = ty;
}

void rays_caster(t_vars *vars, char *ray_maze)
{
	float	st;
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
		//printf("angle = %f, dist = %f, end_x = %f, end_y = %f\n", ray.angle, ray.dist, ray.end_x, ray.end_y);
		if (sgn == 1)
			draw_ray(vars, &ray);
		if (sgn == 2)
			draw_wall(vars, &ray);
		ray.angle += st;
		ray.num_line++;
	}
}
