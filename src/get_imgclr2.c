/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_imgclr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:32:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 21:22:05 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	check_num_rgb(t_vars *vars, char *line, char **rgb, int i)
{
	int	j;

	j = 0;
	(void) vars;
	while (rgb[i][j])
	{
		if (!ft_isdigit(rgb[i][j]))
		{
			free(line);
			ft_frmtrx(rgb);
			close_prog(vars, ERR_LOADCLR);
		}
		j++;
	}
}

static void	get_color_floor_ceil(t_vars *vars, char *line, char **rgb)
{
	int	color;
	int	i;

	i = 0;
	while (rgb[i])
	{
		check_num_rgb(vars, line, rgb, i);
		i++;
	}
	color = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
	if (line[0] == 'F')
		vars->floor_color = color;
	else
		vars->ceiling_color = color;
}

int	import_colors(t_vars *vars, char *line)
{
	char	*val;
	char	**rgb;

	if ((line[0] == 'F' || line[0] == 'C'))
	{
		val = ft_strrchr(line, ' ');
		if (!val)
		{
			free(line);
			close_prog(vars, ERR_LOADCLR);
		}
		rgb = ft_split(++val, ',');
		if (!rgb || ft_arrlen((void **)rgb) != 3)
		{
			free(line);
			if (rgb)
				ft_frmtrx(rgb);
			close_prog(vars, ERR_LOADCLR);
		}
		get_color_floor_ceil(vars, line, rgb);
		ft_frmtrx(rgb);
		return (1);
	}
	return (0);
}
