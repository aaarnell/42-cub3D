/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:06:45 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 21:26:17 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	clean_imgs(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars && vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars && vars->imgs)
	{
		while (vars->imgs[i])
			mlx_destroy_image(vars->mlx, vars->imgs[i++]);
		free(vars->imgs);
	}
}

static void	clean_map(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->map_mx)
	{
		while (vars->map_mx[i])
			free(vars->map_mx[i++]);
		free(vars->map_mx);
	}
}

void	close_prog(t_vars *vars, enum e_err ernum)
{
	clean_imgs(vars);
	clean_map(vars);
	if (vars && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (ernum)
		printf("Error: %s\n", g_err_str[ernum]);
	else if (errno && errno != 60)
		printf("Error: %s\n", strerror(errno));
	exit(1);
}
