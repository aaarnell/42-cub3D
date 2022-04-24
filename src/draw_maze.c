/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_maze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:34:27 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/25 00:23:09 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void pour_floor_ceiling(t_vars *vars)
{
	int	x;
	int y;

	y = 0;
	while (y < vars->hg)
	{
		x = 0;
		while (x < vars->wd)
		{
			if (y < vars->hg / 2)
				my_mlx_pixel_put(vars, x, y, vars->ceiling_color);
			else
				my_mlx_pixel_put(vars, x, y, vars->floor_color);
			x++;
		}
		y++;
	}
}

void vert_line_put(t_vars *vars, int line_h, int size_px, float x, float y)
{
	int		from;
	int		to;
	float	shift;
	int		color;

	shift = 0.005;
	color = M_WLL_CLR;
	if (((int)(x - shift) < (int)(x + shift) ||
		(int)(x - shift) > (int)(x + shift)) &&
		((int)(y - shift) < (int)(y + shift) ||
		(int)(y - shift) > (int)(y + shift)))
		color = M_EMP_CLR;
	from = (WIN_HG - size_px) / 2;
	to = from + size_px;
	while (from < to)
	{
		my_mlx_pixel_put(vars, line_h, from, color);
		from++;
	}
}

void draw_wall(t_vars *vars, float angle, int line_h)
{
	float	i;
	float	y;
	float	x;
	float	size_att;
	int		size_px;

	i = 0.001;
	while (i <= vars->len_ray)
	{
		y = vars->ppy + i * sinf(angle);
		x = vars->ppx + i * cosf(angle);
		if (vars->map_mx[(int)y][(int)x] == '1')
			break ;
		i += 0.001;
	}
	size_att = 1.0 / i / vars->hg_dst_att;
	size_px = WIN_HG * size_att;
	vert_line_put(vars, line_h, size_px, x, y);
}

static char def_prior_coord(t_vars *vars)
{
	float	t_sin;
	float	t_cos;

	t_sin = sinf(vars->ppa);
	t_cos = cosf(vars->ppa);
	if (t_sin < 0)
		t_sin *= (-1);
	if (t_cos < 0)
		t_cos *= (-1);
	if (t_sin > t_cos)
		return ('y');
	return ('x');
}

static void defdef()
{

}

static void rays_caster1(t_vars *vars)
{
	float	t_y;
	float	t_x;
	char	pr_crd;
	float	dstX;
	float	dstY;
	int		i;

	dstX = 1.0;
	dstY = 1.0;
	pr_crd = def_prior_coord(vars);
	if (pr_crd == 'x')
	{
		t_x = (int) vars->ppx;
		if (cosf(vars->ppa) >= 0)
			t_x += dstX;
		dstY = (t_x - vars->ppx) / cosf (vars->ppa) * sinf(vars->ppa);
		t_y = vars->ppy + dstY;
	}
	else
	{
		t_y = (int) vars->ppy;
		if (sinf(vars->ppa) >= 0)
			t_y += dstY;
		dstX = (t_y - vars->ppy) / sinf(vars->ppa) * cosf (vars->ppa);
		t_x = vars->ppx + dstX;
	}
	i = 0;
	while (i <= vars->len_ray)
	{
		t_x = t_x + dstX * i;
		t_y = t_y + dstY * i;
		if (vars->map_mx[(int)t_y][(int)t_x] == '1')
			break ;
		i++;
	}

}

static float round_coord(float cossin, float crd)
{
	float	res_crd;

	res_crd = crd;
	if (cossin < 0)
	{
		res_crd = floorf(crd);
		if (res_crd == crd)
			res_crd -= 1.0;
	}
	else if (cossin > 0)
	{
		res_crd = ceilf(crd);
		if (res_crd == crd)
			res_crd += 1.0;
	}
	return (res_crd);
}

static float def_next_intersect(t_vars *vars, float *x, float *y)
{
	float	hpX;
	float	hpY;
	float	tx;
	float	ty;

	tx = round_coord(cosf(vars->ppa), *x);
	ty = round_coord(sinf(vars->ppa), *y);
	hpX = 0;
	hpY = 0;
	if (cosf(vars->ppa))
		hpX = fabsf((*x - tx) / cosf(vars->ppa));
	if (sinf(vars->ppa))
		hpY = fabsf((*y - ty) / sinf(vars->ppa));
	if (hpX == 0 || (hpY != 0 && hpY <= hpX))
	{
		*x = *x + hpY * cosf(vars->ppa);
		*y = ty;
		return (hpY);
	}
	*x = tx;
	*y = *y + hpX * sinf(vars->ppa);
	return (hpX);
}

static void ray_cast(t_vars *vars)
{
	float	dist;
	float	step;
	float	tx;
	float	ty;

	dist = 0.0;
	tx = vars->ppx;
	ty = vars->ppy;
	while (1)
	{
		step = def_next_intersect(vars, &tx, &ty);
		if (vars->map_mx[(int)ty][(int)tx] == '1')
		{

			break ;
		}
		//проверка на стену
		//если стена, то проверить, не отрицателен ли синус или косинус угла
		//если да, то шаг закончить цикл без прибавления шага
		//иначе прибавить шаг и закончить цикл
		dist += step;
	}

}

void draw_maze(t_vars *vars)
{
	pour_floor_ceiling(vars);
	rays_caster1(vars);
}
