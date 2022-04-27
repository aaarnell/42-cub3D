/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/28 00:10:43 by aarnell          ###   ########.fr       */
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

static void get_size_map(t_vars *vars)
{
	int i;

	i = 0;
	while (vars->map_mx[i])
	{
		if (vars->w_map < (int)ft_strlen(vars->map_mx[i]))
			vars->w_map = ft_strlen(vars->map_mx[i]);
		i++;
	}
	vars->h_map = i;
	vars->len_ray = (int)sqrtf((powf(vars->h_map, 2) + powf(vars->w_map, 2))) + 1;
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
	get_size_map(vars);
}

static void get_player_pos(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	while (vars->map_mx[i])
	{
		j = 0;
		while (vars->map_mx[i][j])
		{
			if (ft_strchr(g_str_sym + 3, vars->map_mx[i][j]))
			{
				vars->ppx = (double)j + 0.5;
				vars->ppy = (double)i + 0.5;
				if (vars->map_mx[i][j]  == 'N')
					vars->ppa = M_PI + M_PI_2;
				if (vars->map_mx[i][j]  == 'W')
					vars->ppa = M_PI;
				if (vars->map_mx[i][j]  == 'S')
					vars->ppa = M_PI_2;
				printf("ppa = %f\n", vars->ppa);
				return ;
			}
			j++;
		}
		i++;
	}
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
	get_player_pos(vars);
	printf("ppx = %f, ppy = %f\n", vars->ppx, vars->ppy);
	printf("w = %d, h = %d\n", vars->w_map, vars->h_map);
}
