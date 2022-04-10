/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:48 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/10 18:56:33 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	check_and_move(t_vars *vars, int tx, int ty)
{
	char	*trg;
	char	*plr;

	trg = &vars->map_mx[ty][tx];
	plr = &vars->map_mx[vars->ppy][vars->ppx];
	if ((*trg == g_str_sym[EXIT] && !vars->cn[ITEM]) || \
	(*trg != g_str_sym[EXIT] && *trg != g_str_sym[WALL]))
	{
		vars->ppx = tx;
		vars->ppy = ty;
		vars->cnt_stp++;
		if (*trg == g_str_sym[ITEM])
			vars->cn[ITEM]--;
		*plr = g_str_sym[EMPTY];
		if (*trg == g_str_sym[EXIT] || *trg == g_str_sym[ENEMY])
		{
			vars->sgn_scr = 1;
			if (*trg == g_str_sym[ENEMY])
				vars->sgn_scr = 2;
			vars->timer = 0;
		}
		if (*trg != g_str_sym[EXIT] && *trg != g_str_sym[ENEMY])
			*trg = g_str_sym[PLAYER];
	}
}

static void	address_definition(t_vars *vars, int keycode, int *tx, int *ty)
{
	if (keycode == 13)
	{
		*tx = vars->ppx;
		*ty = vars->ppy - 1;
	}
	if (keycode == 1)
	{
		*tx = vars->ppx;
		*ty = vars->ppy + 1;
	}
	if (keycode == 0)
	{
		*tx = vars->ppx - 1;
		*ty = vars->ppy;
	}
	if (keycode == 2)
	{
		*tx = vars->ppx + 1;
		*ty = vars->ppy;
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	int	tx;
	int	ty;

	if (vars->sgn_scr != 0)
		return (0);
	if (keycode < 3 || keycode == 13)
	{
		address_definition(vars, keycode, &tx, &ty);
		check_and_move(vars, tx, ty);
	}
	if (keycode == 53)
		close_prog(vars, NONE);
	return (0);
}
