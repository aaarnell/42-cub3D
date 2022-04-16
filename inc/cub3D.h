/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:22:47 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/16 20:58:38 by aarnell          ###   ########.fr       */
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

//# define REVERS_ANIM_SPD 5			//Скорость анимании 1 - самая быстрая
//# define ITER_IN_SECOND 60			//Число циклов mlx_loop примерно = секунде
//# define SEC_SHOW_SCREEN 5			//Секунд показывать финальную заставку
//# define STR_STEPS "Steps:"			//Обозначение счетчика шагов
//# define STR_WON "You won!"			//Текст заставки в случае победы
//# define STR_GAME_OVER "Game over!"	//Текст заставки в случае проигрыша
# define WIN_WD 1920				//Ширина окна в пикселях
# define WIN_HG 1080				//Высотка окна в пикселях
# define MAP_Z 10					//Пикселей на один элемент для миникарты
# define M_PLR_CLR 0x00CC0000		//Цвет игрока на миникарте
# define M_WLL_CLR 0x00FFFFFF		//Цвет стен на миникарте
# define M_EMP_CLR 0x00000000		//Цвет пустот на миникарте
//# define M_

//Символы карты допустимые
static char	*g_str_sym = " 01NSEW";

//Картинки для вывода символов карты на экран
static char	*g_pict_path[] = {
	"./pict/empty.xpm",
	"./pict/enemy.xpm",
	"./pict/exit.xpm",
	"./pict/item_0.xpm",
	"./pict/player.xpm",
	"./pict/wall.xpm",
	NULL
};

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
	"Failed to load required images of walls.",
	"Failed to load required colors floor or ceilling.",
	"There are not enough arguments in the file.",
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
	int		wd;
	int		hg;
	int		floor_color;
	int		ceiling_color;
	int		wdi;
	int		hgi;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	**imgs;
	//void	**anm_itm;
	float	ppx;
	float	ppy;
	// int		*cn;
	// int		cnt_stp;
	// int		sgn_scr;
	//int		timer;
	int		w_map;
	int		h_map;
}	t_vars;

void	read_file(char *file, t_vars *vars);
void	chk_sym(char *line, t_vars *vars, int *player);
int		get_imgcolor(int fd, t_vars *vars, char **line);
void	final_check_map(t_vars *vars);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int		render_frame(t_vars *vars);
void	map_output(t_vars *vars);
//int		load_imgs(t_vars *vars, void **imgs, char **pth);
// int		render_next_frame(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);
int		close_prog(t_vars *vars, enum e_err	ernum);

#endif
