# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 19:58:43 by cnorma            #+#    #+#              #
#    Updated: 2022/04/28 22:51:21 by aarnell          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_LIB		=	./libft
LIBFT		=	libft.a

SRC_MLX		=	./minilibx_opengl_20191021
MLX			=	libmlx.a

NAME 		=	cub3D

SRC_DIR		=	./src/

SRC_FILES	=	main.c			read_file.c		check_file.c	\
				get_imgclr.c	render_frame.c	draw_map.c	\
				draw_maze.c		hooks.c			rays_caster.c	\
				put_texture.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		=	./obj/

OBJ			=	$(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

HEADER		=	inc/cub3D.h

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror -g
FLAGS_O 	=	-Imlx


all:			$(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADER)
				$(CC) $(FLAGS) $(FLAGS_O) -c $< -o $@ -I inc/

$(NAME):		$(OBJ) $(HEADER)
				@$(MAKE) -C $(SRC_LIB)
				@$(MAKE) -C ${SRC_MLX}
				$(CC) $(FLAGS) $(OBJ) $(SRC_LIB)/$(LIBFT) $(SRC_MLX)/$(MLX) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ_DIR):
				@mkdir -p $@

clean:
				$(MAKE) clean -C $(SRC_LIB)
				@$(MAKE) clean -C ${SRC_MLX}
				@rm -rf $(OBJ) $(OBJ_DIR)

fclean:			clean
				@rm -f $(NAME) $(SRC_LIB)/$(LIBFT)

re:				fclean all

.PHONY:			all re clean fclean
