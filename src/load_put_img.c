/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_put_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:54 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/10 18:56:34 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	load_imgs(t_vars *vars, void **imgs, char **pth)
{
	int	num;
	int	wdi;
	int	hgi;

	num = 0;
	while (pth[num])
	{
		imgs[num] = mlx_xpm_file_to_image(vars->mlx, pth[num], &wdi, &hgi);
		if (!imgs[num])
			close_prog(NULL, ERR_LOADIMG);
		if (wdi == hgi && (vars->wdi == 0 || vars->hgi == 0))
		{
			vars->wdi = wdi;
			vars->hgi = hgi;
		}
		else if (wdi != hgi || vars->wdi != wdi || vars->hgi != hgi)
			close_prog(NULL, ERR_SIZIMG);
		num++;
	}
	return (0);
}

static void	put_img_map(t_vars *vars)
{
	char	*ch;
	int		i;
	int		j;
	int		nb;

	i = 0;
	while (vars->map_mx[i])
	{
		j = 0;
		while (vars->map_mx[i][j])
		{
			ch = ft_strchr(g_str_sym, vars->map_mx[i][j]);
			nb = ch - g_str_sym;
			if (!vars->sgn_scr)
				mlx_put_image_to_window(vars->mlx, vars->win, \
				vars->imgs[nb], (vars->wdi * j), (vars->hgi * i));
			else
				mlx_put_image_to_window(vars->mlx, vars->win, \
				vars->imgs[EMPTY], (vars->wdi * j), (vars->hgi * i));
			j++;
		}
		i++;
	}
}

static void	animation_timer_loop(t_vars *vars)
{
	int	i;
	int	sgn;

	i = 0;
	sgn = -1;
	if (!(vars->timer % REVERS_ANIM_SPD))
	{
		while (vars->anm_itm[i])
		{
			if (vars->imgs[ITEM] == vars->anm_itm[i])
				sgn = i;
			i++;
		}
		if (sgn == -1 || !vars->anm_itm[sgn + 1])
			vars->imgs[ITEM] = vars->anm_itm[0];
		else
			vars->imgs[ITEM] = vars->anm_itm[sgn + 1];
	}
	vars->timer++;
}

static void	put_str(t_vars *vars, int base_px, int base_py)
{
	char	*cntr;
	int		cnt_val;
	char	*str;

	cnt_val = vars->cnt_stp;
	str = STR_STEPS;
	if (vars->sgn_scr == 1 || vars->sgn_scr == 2)
	{
		cnt_val = SEC_SHOW_SCREEN - vars->timer / ITER_IN_SECOND;
		str = STR_WON;
		if (vars->sgn_scr == 2)
			str = STR_GAME_OVER;
		base_px = ((vars->wd - 9 * (ft_strlen(str) + 2)) / 2);
		base_py = (vars->hg / 2 - 30);
	}
	cntr = ft_itoa(cnt_val);
	mlx_string_put(vars->mlx, vars->win, base_px, base_py, TEXT_COLOR, str);
	base_px = base_px + 9 * (ft_strlen(str) + 2);
	mlx_string_put(vars->mlx, vars->win, base_px, base_py, TEXT_COLOR, cntr);
	free(cntr);
}

int	render_next_frame(t_vars *vars)
{
	put_img_map(vars);
	put_str(vars, 10, 12);
	if (vars->sgn_scr != 0 && vars->timer / ITER_IN_SECOND > SEC_SHOW_SCREEN)
		close_prog(vars, NONE);
	animation_timer_loop(vars);
	return (0);
}
