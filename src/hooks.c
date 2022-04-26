/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:48 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/26 21:30:47 by aarnell          ###   ########.fr       */
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
	float angle;

	if (keycode == 13)
		angle = vars->ppa;
	if (keycode == 1)
		angle = vars->ppa - M_PI;
	if (keycode == 0)
		angle = vars->ppa - M_PI_2;
	if (keycode == 2)
		angle = vars->ppa + M_PI_2;
	*ty = vars->ppy + MOV_ST * sinf(angle);
	*tx = vars->ppx + MOV_ST * cosf(angle);

}

static void change_direction(t_vars *vars, int src, int keycode, int mouse)
{
	float rad;

	if (!src)
		rad = M_PI * ((float)TRN_KEY / 180);
	else
		rad = M_PI * ((float)TRN_MOUSE / 180);

	if ((!src && keycode == 123) || (src && mouse < 0))
		vars->ppa -= rad;
	else if ((!src && keycode == 124) || (src && mouse > 0))
		vars->ppa += rad;
}

// static void print_player_pos(t_vars *vars)
// {
// 	float angle;

// 	angle = 180 * (vars->ppa / M_PI);
// 	printf("player_pos: x = %f, y = %f, ang = %f\n", vars->ppx, vars->ppy, angle);
// }

int	key_hook(int keycode, t_vars *vars)
{
	float	tx;
	float	ty;

	if (keycode < 3 || keycode == 13)
	{
		address_definition(vars, keycode, &tx, &ty);
		check_and_move(vars, tx, ty);
	}
	if (keycode == 123 || keycode == 124)
		change_direction(vars, 0, keycode, 0);
	if (keycode == 53)
		close_prog(vars, NONE);

//print_player_pos(vars); //для вывода в терминал местоположения пользователя

	return (0);
}

int mouse_move(int x, int y, t_vars *vars)
{
	(void)y;
	//printf("x = %d, y = %d\n", x, y);
	if (x >= 0 && x < vars->wd && y >= 0 && y < vars->hg)
	{
		if (vars->mouse_pos_x != -1)
		{
			if (vars->mouse_pos_x > x)
				change_direction(vars, 1, -1, -1);
			else if (vars->mouse_pos_x < x)
				change_direction(vars, 1, -1, 1);
		}
		vars->mouse_pos_x = x;
	}
	return (0);
}
