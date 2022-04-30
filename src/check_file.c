/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:06:26 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 21:17:36 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	chk_sym(char *line, t_vars *vars, int *player)
{
	int	i;

	i = -1;
	if (!ft_strlen(line) && vars->map_mx)
	{
		free(line);
		close_prog(vars, ERR_INVSYM);
	}
	while (line[++i])
	{
		if (!ft_strchr(g_str_sym, line[i]) || \
			(ft_strchr((g_str_sym + 3), line[i]) && *player))
		{
			free(line);
			close_prog(vars, ERR_INVSYM);
		}
		if (ft_strchr((g_str_sym + 3), line[i]))
			*player = 1;
	}
}

static void	chk_chr_arnd(t_vars *vars, char **map, int v, int h)
{
	int	s;
	int	c;

	if (v == 0 || h == 0 || !map[v + 1] || !map[v][h + 1])
		close_prog(vars, ERR_SUROBS);
	s = v - 1;
	while (s <= (v + 1))
	{
		c = h - 1;
		while (c <= (h + 1))
		{
			if (!ft_strchr((g_str_sym + 1), map[s][c]) || map[s][c] == '\0')
				close_prog(vars, ERR_SUROBS);
			c++;
		}
		s++;
	}
}

void	final_check_map(t_vars *vars)
{
	int		v;
	int		h;
	char	**map;

	map = vars->map_mx;
	v = 0;
	while (map[v])
	{
		h = 0;
		while (map[v][h])
		{
			if (map[v][h] == '0' || ft_strchr(g_str_sym + 3, map[v][h]))
				chk_chr_arnd(vars, map, v, h);
			h++;
		}
		v++;
	}
}
