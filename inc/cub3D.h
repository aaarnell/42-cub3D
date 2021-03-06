/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:22:47 by aarnell           #+#    #+#             */
/*   Updated: 2022/05/07 14:47:17 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <errno.h>
# include <unistd.h>	//close()
# include <stdio.h>
# include <fcntl.h>		//open() и O_XXX-флаги
# include <math.h>

# define US_TEXTURE	1			//Исп. текстуры для стен. 1 = true
# define M_PLR_CLR	0x00CC0000	//Цвет игрока на миникарте
# define M_RAY_CLR	0x0098FB98	//Цвет области видимости на карте
# define M_EMP_CLR	0x00000000	//Цвет пустот на миникарте
# define M_WLL_CLR	0x00FFFFFF	//Цвет стен на миникарте
# define M_NWLL_CLR	0x0000FFFF	//Цвет СЕВЕР-стен в лабиринте (бирюз)
# define M_SWLL_CLR	0x009999FF	//Цвет ЮГ-стен в лабиринте (фиол)
# define M_WWLL_CLR	0x00FFCCFF	//Цвет ЗАПАД-стен в лабиринте (роз)
# define M_EWLL_CLR	0x00FF9999	//Цвет ВОСТОК-стен в лабиринте (корал)
# define WIN_WD		1280		//Ширина окна в пикселях
# define WIN_HG		720			//Высотка окна в пикселях

# define MAP_Z		10		//Пикселей на один элемент для миникарты
# define ANGLE_VIEW	60		//Угол обзора в градусах
# define PLR_SIZE	5		//Размер игрока в пикселях на миникарте

# define TRN_KEY	10		//Поворот в градусах за одно нажатие <-/->
# define TRN_MOUSE	2		//Поворот в градусах за 1 ед. сдвига мыши
# define MOV_ST		0.2		//Шаг игрока, доля от размера 1 блока карты

//Символы карты допустимые
static char	*g_str_sym = " 01NSEW";

//ID изображений стен, по которым программа ищет их адреса во вводном файле
static char	*g_id_img[] = {
	"NO",
	"SO",
	"WE",
	"EA",
	NULL
};

//Нумерованный список id изображений стен
enum	e_pict {
	NO,
	SO,
	WE,
	EA
};

//Количество и последовательность элементов в переменных
//g_err_str, e_err должны соответствовать друг другу

//Текст выводимых ошибок
static char	*g_err_str[] = {
	"No errors.",
	"Error in the number of program arguments.",
	"Memory allocation error.",
	"Incorrect extension, an attempt to open a \
directory, or an error opening a file.",
	"Failed to load required images of walls.",
	"Failed to load required colors floor or ceilling.",
	"There are not enough or redundant arguments in the file.",
	"The file is missing a map.",
	"The size of the pictures is different.",
	"Invalid characters on the map layout or \
more than one player character.",
	"The map is not surrounded by obstacles.",
	"There are not enough required characters or extra ones.",
	NULL
};

//Числовые значения ошибок
enum	e_err {
	NONE,
	ERR_ARGNUM,
	ERR_ALLOC,
	ERR_FILE,
	ERR_LOADIMG,
	ERR_LOADCLR,
	ERR_ARGNMFL,
	ERR_MISMPFL,
	ERR_SIZIMG,
	ERR_INVSYM,
	ERR_SUROBS,
	ERR_REQCHAR
};

typedef struct s_vars{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	char	**map_mx;
	int		floor_color;
	int		ceiling_color;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	**imgs;
	char	**addrs;
	int		wdi;
	int		hgi;
	int		bpp;
	int		ll;
	double	ppx;
	double	ppy;
	double	ppa;
	double	hlf_vw_angle;
	double	win_dist;
	double	hg_dst_att;
	int		w_map;
	int		h_map;
	int		len_ray;
	int		mouse_pos_x;
}	t_vars;

typedef struct s_ray{
	double		angle;
	double		dist;
	double		end_x;
	double		end_y;
	int			num_line;
	enum e_pict	side;
	double		prop_h;
	double		prop_v;
}	t_ray;

void	read_file(char *file, t_vars *vars);
void	chk_sym(char *line, t_vars *vars, int *player);
int		import_colors(t_vars *vars, char *line);
void	get_imgcolor(int fd, t_vars *vars, char **line);
void	final_check_map(t_vars *vars);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	put_texture(t_vars *vars, int size_px, t_ray *ray);
void	rays_caster(t_vars *vars, char *ray_maze);
int		render_frame(t_vars *vars);
void	draw_maze(t_vars *vars);
void	draw_wall(t_vars *vars, t_ray *ray);
void	draw_ray(t_vars *vars, t_ray *ray);
void	draw_map(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);
int		mouse_move(int x, int y, t_vars *vars);
void	close_prog(t_vars *vars, enum e_err ernum);

#endif
