NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
#-------folder-------#
UTILS = utils
SRC = minishell.c \
	$(UTILS)/ft_split.c $(UTILS)/ft_strlen.c $(UTILS)/ft_strdup.c $(UTILS)/ft_substr.c $(UTILS)/ft_strjoin.c $(UTILS)/ft_putendl_fd.c \
	$(UTILS)/ft_lstsize.c  $(UTILS)/ft_isalnum.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
	@echo "\033[0;32m Minishell compiled\033[0m"

%.o: %.c minishell.h
	@printf "\033[0;32m Compiling minishell: \033[0;33m$<\033[0m\r"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[0;32m Cleaned\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;32m Fcleaned\033[0m"

re: fclean all
