/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:28:21 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/28 00:34:28 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	close_prog(t_vars *vars, enum e_err	ernum)
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
	// int	ln;
	// int	i;

	// i = 0;
	// ln = ft_strlen(g_str_sym);

	//vars->imgs = (void **)malloc(sizeof(void *) * (sizeof(enum e_pict) + 1));
	vars->imgs = (void **)ft_calloc(sizeof(void *), (sizeof(enum e_pict) + 1));
	if (!vars->imgs)
		return (-1);
	//vars->imgs[sizeof(enum	e_pict)] = NULL;

	// vars->cn = (int *)malloc(sizeof(int) * ln);
	// if (!vars->cn)
	// 	return (0);
	// while (i < ln)
	// 	vars->cn[i++] = 0;
	// ln = 0;
	// while (g_anm_itm_path[ln])
	// 	ln++;
	// vars->anm_itm = (void **)malloc(sizeof(void *) * (ln + 1));
	// if (!vars->anm_itm)
	// 	return (0);
	// vars->anm_itm[ln] = NULL;
	return (0);
}


static void	struct_init(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = NULL;
	vars->img = NULL;
	vars->addr = NULL;
	vars->map_mx = NULL;
	vars->wd = WIN_WD;
	vars->hg = WIN_HG;
	vars->floor_color = -1;
	vars->ceiling_color = -1;
	vars->wdi = 0;
	vars->hgi = 0;
	vars->bits_per_pixel = 0;
	vars->line_length = 0;
	vars->endian = 0;
	vars->imgs = NULL;
	// vars->anm_itm = NULL;
	vars->ppx = 0;
	vars->ppy = 0;
	vars->ppa = 0;
	vars->hlf_vw_angle = M_PI / ((double)180 / ((double)ANGLE_VIEW / 2));
	vars->win_dist = (double)WIN_WD / (double)WIN_HG / 2 / tan(vars->hlf_vw_angle);
	vars->hg_dst_att = 1.0 / vars->win_dist;
	//vars->cn = NULL;
	// vars->cnt_stp = 0;
	// vars->sgn_scr = 0;
	// vars->timer = 0;
	vars->w_map = 0;
	vars->h_map = 0;
	vars->mouse_pos_x = -1;
	if (alloc_init(vars) == -1)
	 	close_prog(NULL, ERR_ALLOC);
}

// static void print_map(char **map)
// {
// 	int	v;

// 	v = 0;
// 	while (map[v])
// 		ft_putendl_fd(map[v++], 1);
// }

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		close_prog(NULL, ERR_ARGNUM);
	struct_init(&vars);
	read_file(argv[1], &vars);
	//print_map(vars.map_mx);
	// load_imgs(&vars, vars.imgs, g_pict_path);
	// load_imgs(&vars, vars.anm_itm, g_anm_itm_path);
	vars.win = mlx_new_window(vars.mlx, vars.wd, vars.hg, "cub3D!");
	vars.img = mlx_new_image(vars.mlx, vars.wd, vars.hg);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	mlx_loop_hook(vars.mlx, render_frame, &vars);
// render_frame(&vars);
	mlx_hook (vars.win, 2, 0L, key_hook, &vars);
	mlx_hook (vars.win, 6, 0L, mouse_move, &vars);
	mlx_hook (vars.win, 17, 0L, cross_exit, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
