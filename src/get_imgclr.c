/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_imgclr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:19:37 by aarnell           #+#    #+#             */
/*   Updated: 2022/05/01 13:38:07 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	get_image_data(t_vars *vars, char *pth, int i)
{
	int	wd;
	int	hg;

	vars->imgs[i] = mlx_xpm_file_to_image(vars->mlx, \
		pth, &wd, &hg);
	if (!vars->imgs[i])
		return (0);
	vars->addrs[i] = mlx_get_data_addr(vars->imgs[i], \
		&vars->bpp, &vars->ll, &vars->endian);
	if (!vars->addrs[i])
		return (0);
	if (vars->wdi && vars->wdi != wd)
		return (0);
	if (vars->hgi && vars->hgi != hg)
		return (0);
	vars->wdi = wd;
	vars->hgi = hg;
	return (1);
}

static int	import_images(t_vars *vars, char *line)
{
	int		i;
	char	*pth;

	i = 0;
	while (g_id_img[i])
	{
		if (!ft_strncmp(line, g_id_img[i], ft_strlen(g_id_img[i])))
		{
			pth = ft_strrchr(line, ' ');
			if (vars->imgs[i] || !get_image_data(vars, ++pth, i))
			{
				free(line);
				close_prog(vars, ERR_LOADIMG);
			}
			return (1);
		}
		i++;
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
		if (!ft_strlen(ln) || import_images(vars, ln) \
			|| import_colors(vars, ln))
		{
			free(ln);
			continue ;
		}
		if (check_fill_img_clr(vars))
		{
			free(ln);
			close_prog(vars, ERR_ARGNMFL);
		}
		*line = ln;
		return ;
	}
	free(ln);
	close_prog(vars, ERR_MISMPFL);
	return ;
}
