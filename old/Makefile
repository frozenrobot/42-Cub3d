SRC = main.c 
OBJ = main.o 
NAME = mlx

all: $(NAME)

$(NAME):
	gcc main.c -framework OpenGL -framework AppKit -lmlx -Lmlx -o mlxprog

clean:
	rm -f mlxprog
	