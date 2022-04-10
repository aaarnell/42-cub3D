SRC_LIB		=	./libft
LIBFT		=	libft.a

NAME 		= 	so_long

HD			=	so_long.h
HD_B		=	so_long_bonus.h

FLAGS		= 	-Wall -Werror -Wextra -g
FLAGS_O 	=	-Imlx

SRS			= 	check_count.c		gnl.c		hooks.c		\
				load_put_img.c		main.c		parc_map.c

SRS_B		= 	check_count_bonus.c		gnl_bonus.c		hooks_bonus.c		\
				load_put_img_bonus.c	main_bonus.c	parc_map_bonus.c

OBJS		=	$(SRS:.c=.o)

OBJS_B		=	$(SRS_B:.c=.o)

all bonus	:
				$(MAKE) $(NAME)

bonus		:	export BONUS_MODE := 1

%.o 		:	%.c $(if $(BONUS_MODE), $(HD_B), $(HD))
				gcc $(FLAGS) $(FLAGS_O) -c $< -o $@ -I $(if $(BONUS_MODE), $(HD_B), $(HD))

$(NAME)		: 	$(if $(BONUS_MODE), $(OBJS_B), $(OBJS))
				$(MAKE) -C $(SRC_LIB)
				gcc $(FLAGS) $(if $(BONUS_MODE), $(OBJS_B), $(OBJS)) $(SRC_LIB)/$(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean		:
				$(MAKE) clean -C $(SRC_LIB)
				rm -f $(OBJS) $(OBJS_B)

fclean		:	clean
				rm -f $(NAME) $(SRC_LIB)/$(LIBFT)

re 			:	fclean all

re_bonus	:	fclean bonus

.PHONY: all bonus clean fclean re re_bonus
