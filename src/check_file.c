/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:19:37 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/12 15:43:03 by aarnell          ###   ########.fr       */
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
	return (0xFF000000 | ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]));
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
			close_prog(NULL, ERR_LOADIMG);
		}
		rgb = ft_split(++val, ',');
		if (ft_arrlen(rgb) != 3)
		{
			free(line);
			ft_frmtrx(rgb);
			close_prog(NULL, ERR_LOADIMG);
		}
		if (line[0] == 'F')
			vars->floor_color = create_rgb(rgb);
		else
			vars->ceilling_color = create_rgb(rgb);
		ft_frmtrx(rgb);
		return (1);
	}
	return (0);
}

int get_intro_info(int fd, t_vars *vars, char **line)
{
	char	*ln;
	//получим вводные данные
	//идем по строкам
	//проверяем - какой параметр из 6 возможных
	while (ft_get_next_line(fd, &ln))
	{
		if (!ft_strlen(ln) || check_import_image(vars, ln) \
			 || check_import_color(vars, ln))
		{
			free(ln);
			continue ;
		}
		else
		{
			//здесь проверка - все ли картинки и цвета считаны
				//если ДА, запись ln в line и выход, т.к. если все проверки выше строка не прошла, значит это начало карты
				//если НЕТ, то вернуть ошибку
				//остановить цикл, завершить функцию
			;
		}
	}
	//если цикл дошел до сюда, значит карты в файле нет, и он прощелкал до конца. Обработать ошибку
	return (0);
}
