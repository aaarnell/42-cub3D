/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_imgclr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:19:37 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/14 21:44:59 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int check_import_image(t_vars *vars, char *line)
{
	int	i;
	char *pth;

	i = 0;
	while (g_id_img[i])
	{
		if (!ft_strncmp(line, g_id_img[i], ft_strlen(g_id_img[i])))
		{
			pth = ft_strrchr(line, ' ');
			vars->imgs[i] = mlx_xpm_file_to_image(vars->mlx, ++pth, &vars->wdi, &vars->hgi);
			//возможно стоит чекать размеры изображений, чтобы были одинаковыми или это некритично?
			if (!vars->imgs[i])
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

static int	create_rgb(char **rgb)
{
	return (ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]));
}

static int check_import_color(t_vars *vars, char *line)
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
		//возможно тут нужна проверка аргументов на валидность - они должны быть цифрами
		//а может такая проверка есть в ft_atoi
		if (ft_arrlen((void **)rgb) != 3)
		{
			free(line);
			ft_frmtrx(rgb);
			close_prog(NULL, ERR_LOADCLR);
		}
		if (line[0] == 'F')
			vars->floor_color = create_rgb(rgb);
		else
			vars->ceiling_color = create_rgb(rgb);
		ft_frmtrx(rgb);
		return (1);
	}
	return (0);
}

static int check_fill_img_clr(t_vars *vars)
{
	int		i;

	i = (int)sizeof(enum e_pict) - 1;
	while (i > -1 && vars->imgs[i])
		i--;
	if (i != -1 || vars->floor_color == -1 || vars->ceiling_color == -1)
		return (1);
	return (0);
}
//возможно стоит сделать возврат void, т.к. в случае ошибок программа выходит внутри функций.
int get_imgcolor(int fd, t_vars *vars, char **line)
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
		return (0);
	}
	free(ln);
	close_prog(NULL, ERR_MISMPFL);
	return (1);
}
