NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
#-------folder-------#
UTILS = utils
SRC = minishell.c \
	$(UTILS)/ft_split.c $(UTILS)/ft_strlen.c $(UTILS)/ft_strdup.c $(UTILS)/ft_substr.c
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
