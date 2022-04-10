/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:11:06 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/10 18:56:32 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	check_length_get_width(char *line, int *wd)
{
	int	wdl;

	wdl = ft_strlen(line);
	if (!wdl)
		return (0);
	if (!*wd)
		*wd = wdl;
	else if (*wd != wdl)
		return (0);
	return (1);
}

static void	cnt_sym(t_vars *vars, int c)
{
	char	*ch;
	int		i;

	ch = ft_strchr(g_str_sym, c);
	i = ch - g_str_sym;
	vars->cn[i] += 1;
}

int	cnt_chk_sym(char *line, t_vars *vars)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(g_str_sym, line[i]))
			return (0);
		cnt_sym(vars, line[i]);
		if ((!vars->ppx || !vars->ppy) && line[i] == g_str_sym[PLAYER])
		{
			vars->ppx = i;
			vars->ppy = vars->hg;
		}
		i++;
	}
	return (1);
}

void	fnl_chk_sym_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map_mx[i])
	{
		j = 0;
		while (vars->map_mx[i][j])
		{
			if ((i == 0 || i == (vars->hg - 1) || j == 0 || \
			j == (vars->wd - 1)) && vars->map_mx[i][j] != g_str_sym[WALL])
				close_prog(NULL, ERR_SUROBS);
			j++;
		}
		i++;
	}
	if (!vars->cn[EMPTY] || !vars->cn[EXIT] || !vars->cn[ITEM] || \
	!vars->cn[PLAYER] || !vars->cn[WALL] || vars->cn[PLAYER] > 1)
		close_prog(NULL, ERR_REQCHAR);
}
