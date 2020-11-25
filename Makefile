.PHONY: all clean fclean re norme

NAME = shell

SRC = main.c get_next_line/get_next_line.c ft_realloc.c

SRCO = $(SRC:.c=.o)

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