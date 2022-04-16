/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:48 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/16 20:00:19 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	check_and_move(t_vars *vars, float tx, float ty)
{
	char	*trg;
	char	*plr;

	if ((int)tx != (int)vars->ppx || (int)ty != (int)vars->ppy)
	{
		trg = &vars->map_mx[(int)ty][(int)tx];
		plr = &vars->map_mx[(int)vars->ppy][(int)vars->ppx];
		if (*trg == '0')
		{
			*trg = *plr;
			*plr = '0';
			vars->ppx = tx;
			vars->ppy = ty;
		}
	}
	else
	{
		vars->ppx = tx;
		vars->ppy = ty;
	}
}

static void	address_definition(t_vars *vars, int keycode, float *tx, float *ty)
{
	if (keycode == 13)
	{
		*tx = vars->ppx;
		*ty = vars->ppy - 0.1;
	}
	if (keycode == 1)
	{
		*tx = vars->ppx;
		*ty = vars->ppy + 0.1;
	}
	if (keycode == 0)
	{
		*tx = vars->ppx - 0.1;
		*ty = vars->ppy;
	}
	if (keycode == 2)
	{
		*tx = vars->ppx + 0.1;
		*ty = vars->ppy;
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	float	tx;
	float	ty;

	if (keycode < 3 || keycode == 13)
	{
		address_definition(vars, keycode, &tx, &ty);
		check_and_move(vars, tx, ty);
	}
	if (keycode == 53)
		close_prog(vars, NONE);
	printf("player_pos: x = %f, y = %f\n", vars->ppx, vars->ppy);
	return (0);
}
