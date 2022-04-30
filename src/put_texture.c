/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:31:12 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/30 19:58:00 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static enum e_pict	def_side(t_ray *ray)
{
	double	xps;
	double	xms;
	double	yps;
	double	yms;

	xps = ray->end_x + 0.000001;
	xms = ray->end_x - 0.000001;
	yps = ray->end_y + 0.000001;
	yms = ray->end_y - 0.000001;
	if ((int)xms != (int)xps && (int)yms == (int)yps)
	{
		if (cos(ray->angle) < 0)
			return (EA);
		return (WE);
	}
	else
	{
		if (sin(ray->angle) < 0)
			return (NO);
		return (SO);
	}
}

static double	def_prop(t_ray *ray)
{
	double	res;
	double	crd;

	res = 0.0;
	if (ray->side == NO || ray->side == EA)
	{
		crd = ray->end_x;
		if (ray->side == EA)
			crd = ray->end_y;
		res = crd - floor(crd);
	}
	else if (ray->side == SO || ray->side == WE)
	{
		crd = ray->end_x;
		if (ray->side == WE)
			crd = ray->end_y;
		res = ceil(crd) - crd;
	}
	return (res);
}

static void	my_mlx_pxl_frm_img_put(t_vars *vars, t_ray *ray, int ty)
{
	char	*source;
	char	*target;
	int		sx;
	int		sy;
	int		tx;

	tx = ray->num_line;
	sx = (double)vars->wdi * ray->prop_h;
	sy = (double)vars->hgi * ray->prop_v;
	source = vars->addrs[ray->side] + (sy * vars->ll + sx * (vars->bpp / 8));
	target = vars->addr + (ty * vars->line_length \
		+ tx * (vars->bits_per_pixel / 8));
	*(unsigned int *) target = *(unsigned int *) source;
}

void	put_texture(t_vars *vars, int size_px, t_ray *ray)
{
	int			from;
	int			to;
	int			i;

	ray->side = def_side(ray);
	ray->prop_h = def_prop(ray);
	from = (WIN_HG - size_px) / 2;
	to = WIN_HG;
	i = 0;
	if (size_px < WIN_HG)
		to = from + size_px;
	while (from + i < to)
	{
		if (from + i >= 0)
		{
			ray->prop_v = 1.0 - (double)(size_px - i) / (double) size_px;
			my_mlx_pxl_frm_img_put(vars, ray, from + i);
		}
		i++;
	}
}
