/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/13 20:10:20 by aarnell          ###   ########.fr       */
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
		//if (!chk_spcstr(&line))
		//	add_str_to_map(vars, line);
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
	//int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_prog(NULL, NONE);
	//получить вводные данные
	get_imgcolor(fd, vars, &line);
	//затем распарсить карту
	get_map(fd, vars, line);

	/*get_width_height(file, vars);
	vars->map_mx = (char **)malloc(sizeof(char *) * (vars->hg + 1));
	if (!vars->map_mx)
		close_prog(NULL, ERR_ALLOC);
	i = 0;
	while (ft_get_next_line(fd, &line))
		vars->map_mx[i++] = line;
	free(line);
	vars->map_mx[i] = NULL;
	fnl_chk_sym_map(vars);
	vars->wd = vars->wd * vars->wdi;
	vars->hg = vars->hg * vars->hgi;
	close(fd);*/
}
