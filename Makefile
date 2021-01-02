.PHONY: all clean fclean re norme

NAME = minishell

SRC =	utils/ft_strdup.c utils/ft_strlen.c utils/ft_strjoin.c utils/ft_strlcpy.c utils/ft_strnstr.c \
		utils/ft_strchr.c utils/ft_strncmp.c utils/ft_memcpy.c \
		utils/ft_putstr_fd.c utils/ft_putchar_fd.c utils/ft_putendl_fd.c \
		utils/ft_isalnum.c utils/ft_isalpha.c utils/ft_isdigit.c \
		utils/ft_itoa.c utils/ft_atoi.c \
		utils/ft_realloc.c utils/ft_double_realloc.c utils/ft_strtok.c utils/free_arr.c \
		main.c get_next_line/get_next_line.c \
		launch.c error.c list_cmd.c signals.c pipes.c redirects.c \
		parsing.c parsing_env.c parsing_redirects.c parsing_quotes.c \
		cmd_echo.c cmd_cd.c cmd_pwd.c cmd_export.c cmd_unset.c cmd_env.c cmd_exit.c

SRCO = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCO) minishell.h
	@gcc $(SRCO) -o $(NAME)

%.o:%.c minishell.h
	@gcc -g -c $< -o $@

clean:
	@rm -f $(SRCO)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norme:
	@norminette $(SRC) minishell.h get_next_line/get_next_line.h utils/utils.h

