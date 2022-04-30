/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_imgclr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:19:37 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 19:16:20 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	check_import_image(t_vars *vars, char *line)
{
	int		i;
	char	*pth;
	int		end;

	i = 0;
	while (g_id_img[i])
	{
		if (!ft_strncmp(line, g_id_img[i], ft_strlen(g_id_img[i])))
		{
			pth = ft_strrchr(line, ' ');
			vars->imgs[i] = mlx_xpm_file_to_image(vars->mlx, \
				++pth, &vars->wdi, &vars->hgi);
			vars->addrs[i] = mlx_get_data_addr(vars->imgs[i], \
				&vars->bpp, &vars->ll, &end);
			if (!vars->imgs[i] || !vars->addrs[i])
			{
				free(line);
				close_prog(NULL, ERR_LOADIMG);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

static void	get_color_floor_ceil(t_vars *vars, char *line, char **rgb)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
			{
				free(line);
				ft_frmtrx(rgb);
				close_prog(NULL, ERR_LOADCLR);
			}
			j++;
		}
		i++;
	}
	color = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
	if (line[0] == 'F')
		vars->floor_color = color;
	else
		vars->ceiling_color = color;
}

static int	check_import_color(t_vars *vars, char *line)
{
	char	*val;
	char	**rgb;

	if ((line[0] == 'F' || line[0] == 'C'))
	{
		val = ft_strrchr(line, ' ');
		if (!val)
		{
			free(line);
			close_prog(NULL, ERR_LOADCLR);
		}
		rgb = ft_split(++val, ',');
		if (!rgb || ft_arrlen((void **)rgb) != 3)
		{
			free(line);
			if (rgb)
				ft_frmtrx(rgb);
			close_prog(NULL, ERR_LOADCLR);
		}
		get_color_floor_ceil(vars, line, rgb);
		ft_frmtrx(rgb);
		return (1);
	}
	return (0);
}

static int	check_fill_img_clr(t_vars *vars)
{
	int		i;

	i = (int) sizeof(enum e_pict) - 1;
	while (i > -1 && vars->imgs[i])
		i--;
	if (i != -1 || vars->floor_color == -1 || vars->ceiling_color == -1)
		return (1);
	return (0);
}

void	get_imgcolor(int fd, t_vars *vars, char **line)
{
	char	*ln;

	while (ft_get_next_line(fd, &ln))
	{
		if (!ft_strlen(ln) || check_import_image(vars, ln) \
			|| check_import_color(vars, ln))
		{
			free(ln);
			continue ;
		}
		if (check_fill_img_clr(vars))
		{
			free(ln);
			close_prog(NULL, ERR_ARGNMFL);
		}
		*line = ln;
		return ;
	}
	free(ln);
	close_prog(NULL, ERR_MISMPFL);
	return ;
}
