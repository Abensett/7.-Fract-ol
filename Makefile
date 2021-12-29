GREEN   = \033[1;32m
WHITE   = \033[0;m

SRC = 	ft_error_handlers.c \
		ft_fractol.c \
		ft_fractol_utils.c \
		ft_mandelbrot.c \
		ft_julia.c \

OBJ= $(SRC:.c=.o)
OBJ	:= $(addprefix obj/,${OBJ})

CC = gcc

FL_MLX	= -ldl -lmlx -Lmlx -lm -lXext -lX11 -Imlx mlx/libmlx.a
CFLAGS = -g  -I includes
## -lmlx -lbass
NAME = fractol

all:			$(NAME)

fractol :		$(OBJ)
				@make -C libft
				@make bonus -C libft
				$(CC) ${CFLAGS} ${OBJ} -o $(NAME) $(FL_MLX) libft/libft.a

obj/%.o:src/%.c
				@mkdir -p obj
				$(CC) -o $@ -c $< $(CFLAGS)

clean:
				@rm -f $(OBJ) core
				@make -C libft clean
				@printf "\n[$(GREEN)cleaned$(WHITE)] .o FILES and libft \n"

fclean:			clean
				@rm -f $(NAME) libft/libft.a
				@printf "\n[$(GREEN)cleaned$(WHITE)] $(NAME) libft.a \n"

re:				fclean all

.PHONY:			all clean fclean re
