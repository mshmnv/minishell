.PHONY: all clean fclean re norme

NAME = shell

SRC =	main.c get_next_line/get_next_line.c \
		ft_realloc.c ft_strtok.c free_arr.c \
		launch.c error.c list_cmd.c parsing.c signals.c pipes.c \
		cmd_echo.c cmd_cd.c cmd_pwd.c cmd_export.c cmd_unset.c cmd_env.c cmd_exit.c

SRCO = $(SRC:.c=.o)

LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCO) $(LIBFT) minishell.h
	@gcc libft/libft.a $(SRCO) -o $(NAME)

$(LIBFT):
	@make -C ./libft

%.o:%.c minishell.h
	@gcc -c $< -o $@

clean:
	@rm -f $(SRCO)
	@make clean -C ./libft/

fclean: clean
	@rm -f $(NAME)

re: fclean all

norme:
	@norminette $(SRC) minishell.h ./libft/*.c