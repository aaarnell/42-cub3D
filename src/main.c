/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:28:21 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 19:56:13 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	close_prog(t_vars *vars, enum e_err ernum)
{
	if (vars && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (ernum)
		printf("Error: %s\n", g_err_str[ernum]);
	else if (errno && errno != 60)
		printf("Error: %s\n", strerror(errno));
	exit(1);
	return (0);
}

static int	cross_exit(t_vars *vars)
{
	close_prog(vars, NONE);
	return (0);
}

static int	alloc_init(t_vars *vars)
{
	vars->imgs = (void **)ft_calloc(sizeof(void *), (sizeof(enum e_pict) + 1));
	if (!vars->imgs)
		return (-1);
	vars->addrs = (char **)ft_calloc(sizeof(char *), (sizeof(enum e_pict) + 1));
	if (!vars->addrs)
		return (-1);
	return (0);
}

static void	struct_init(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = NULL;
	vars->img = NULL;
	vars->addr = NULL;
	vars->map_mx = NULL;
	vars->floor_color = -1;
	vars->ceiling_color = -1;
	vars->wdi = 0;
	vars->hgi = 0;
	vars->bits_per_pixel = 0;
	vars->line_length = 0;
	vars->imgs = NULL;
	vars->ppx = 0;
	vars->ppy = 0;
	vars->ppa = 0;
	vars->hlf_vw_angle = M_PI / ((double)180 / ((double)ANGLE_VIEW / 2));
	vars->win_dist = (double)WIN_WD / (double)WIN_HG \
		/ 2 / tan(vars->hlf_vw_angle);
	vars->hg_dst_att = 1.0 / vars->win_dist;
	vars->w_map = 0;
	vars->h_map = 0;
	vars->mouse_pos_x = -1;
	if (alloc_init(vars) == -1)
		close_prog(NULL, ERR_ALLOC);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		close_prog(NULL, ERR_ARGNUM);
	struct_init(&vars);
	read_file(argv[1], &vars);
	vars.win = mlx_new_window(vars.mlx, WIN_WD, WIN_HG, "cub3D!");
	vars.img = mlx_new_image(vars.mlx, WIN_WD, WIN_HG);
	vars.addr = mlx_get_data_addr(vars.img, \
		&vars.bits_per_pixel, &vars.line_length, &vars.endian);
	mlx_loop_hook(vars.mlx, render_frame, &vars);
	mlx_hook (vars.win, 2, 0L, key_hook, &vars);
	mlx_hook (vars.win, 6, 0L, mouse_move, &vars);
	mlx_hook (vars.win, 17, 0L, cross_exit, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
