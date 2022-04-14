/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/14 21:20:32 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void add_str_to_map(t_vars *vars, char *line)
{
	char	**tmp;

	tmp = ft_add_str_to_arr(vars->map_mx, line);
	if (!tmp)
	{
		free(line);
		close_prog(NULL, NONE);
	}
	if (vars->map_mx)
		ft_frmtrx(vars->map_mx);
	vars->map_mx = tmp;
}

static void get_map(int fd, t_vars *vars, char *line)
{
	int		res;
	int		player;

	res = 1;
	player = 0;
	while (res)
	{
		chk_sym(line, vars, &player);
		add_str_to_map(vars, line);
		free(line);
		res = ft_get_next_line(fd, &line);
	}
	free(line);
	final_check_map(vars);
}

void	read_file(char *file, t_vars *vars)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_prog(NULL, NONE);
	get_imgcolor(fd, vars, &line);
	get_map(fd, vars, line);
}
