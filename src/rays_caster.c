/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_caster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:45:24 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/19 22:54:22 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void rays_caster(t_vars *vars, char *ray_maze)
{
	float	angle;
	float	st;
	int		sgn;

	sgn = 0;
	if (!ft_strncmp(ray_maze, "rays", 4))
		sgn = 1;
	if (!ft_strncmp(ray_maze, "maze", 4))
		sgn = 2;
	if (!sgn)
		return ;
	st = vars->hlf_vw_angle * 2 / WIN_WD;
	angle = vars->ppa - vars->hlf_vw_angle;
	while (angle < vars->ppa + vars->hlf_vw_angle)
	{
		if (sgn == 1)
			draw_ray(vars, angle);
		if (sgn == 2)
			draw_wall(vars, angle);
		angle += st;
	}
}
