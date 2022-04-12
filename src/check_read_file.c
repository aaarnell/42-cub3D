/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_read_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:06:26 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/12 22:35:11 by aarnell          ###   ########.fr       */
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
		close_prog(NULL, ERR_INVSYM);
	}
	while (line[++i])
	{
		if (!ft_strchr(g_str_sym, line[i]) || \
			(ft_strchr((g_str_sym + 3), line[i]) && *player))
		{
			free(line);
			close_prog(NULL, ERR_INVSYM);
		}
		if (ft_strchr((g_str_sym + 3), line[i]))
			*player = 1;
	}
}

int chk_spcstr(t_vars *vars, char *line)
{
	int	i;
	int	cnt_spc;

	i = -1;
	cnt_spc = 0;
	while (line[++i])
	{
		if (line[i] == ' ')
			cnt_spc++;
	}
	if (cnt_spc == ft_strlen(line))
	{
		if (vars->map_mx)
		{
			free(line);
			close_prog(NULL, ERR_INVSYM);
		}
		return (1);
	}
	return (0);
}

void final_check_map(t_vars *vars)
{

}
