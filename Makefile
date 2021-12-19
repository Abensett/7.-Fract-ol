SRC = main.c
OBJ= $(SRC:.c=.o)
OBJ	:= $(addprefix obj/,${OBJ})

CC = gcc

FL_MLX	= -ldl -lmlx -Lmlx -lm -lXext -lX11 -Imlx mlx/libmlx.a
CFLAGS = -g  -I includes
## -lmlx -lbass 
NAME = fractol

all:			$(NAME)

fractol :	$(OBJ) 
				@make -C ./mlx
				$(CC) ${CFLAGS} ${OBJ} -o $(NAME) $(FL_MLX)

obj/%.o:src/%.c
				@mkdir -p obj
				$(CC) -o $@ -c $< $(CFLAGS)

clean:
				rm -f $(OBJ) core

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re