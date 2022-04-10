/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/10 21:25:09 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
/*
static void	get_width_height(char *file, t_vars *vars)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_prog(NULL, NONE);
	while (ft_get_next_line(fd, &line))
	{
		if (!check_length_get_width(line, &vars->wd))
		{
			free(line);
			close_prog(NULL, ERR_DIFLIN);
		}
		if (!cnt_chk_sym(line, vars))
		{
			free(line);
			close_prog(NULL, ERR_INVSYM);
		}
		free(line);
		vars->hg++;
	}
	free(line);
	close(fd);
}

void	read_file(char *file, t_vars *vars)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_prog(NULL, NONE);
	get_width_height(file, vars);
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
	close(fd);
}*/





void	read_file(char *file, t_vars *vars)
{
	int		fd;
	//int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_prog(NULL, NONE);
	//получить вводные данные
	get_intro_info(fd, vars, &line);
	//затем распарсить карту
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
