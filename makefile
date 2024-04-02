NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address 
#-------folder-------#
UTILS = utils
LEXER = lexer
HANDLE_ERRORS=handle_errors
EXPANDER=expander
EXECUTION=execution
BUILT_IN=built_in
PIPE=pipe
GC=gc
READLINE=$(shell brew --prefix readline)/lib
READLINE1=$(shell brew --prefix readline)/include
#-------files-------#
SRC =minishell.c \
	$(UTILS)/ft_split.c $(UTILS)/ft_strlen.c $(UTILS)/ft_strdup.c $(UTILS)/ft_substr.c $(UTILS)/ft_strjoin.c $(UTILS)/ft_putendl_fd.c \
	$(UTILS)/ft_lstsize.c  $(UTILS)/ft_isalnum.c $(UTILS)/ft_itoa.c $(UTILS)/ft_lstlast.c \
	$(LEXER)/ft_tonken.c  $(LEXER)/ft_tonken_utils.c \
	$(HANDLE_ERRORS)/handle_errors.c \
	$(EXPANDER)/expander.c $(EXPANDER)/expander_utils.c \
	$(GC)/ft_free.c \
	$(EXECUTION)/execution.c $(EXECUTION)/execution_tools.c \
	$(BUILT_IN)/built_in_tools.c $(BUILT_IN)/cd.c $(BUILT_IN)/env.c $(BUILT_IN)/export.c $(BUILT_IN)/pwd.c $(BUILT_IN)/unset.c $(BUILT_IN)/echo.c \
	$(PIPE)/ft_pipe.c sigs/signals.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -L $(READLINE) -o $(NAME)
	@echo "\033[0;32m Minishell compiled\033[0m"

%.o: %.c minishell.h
	@printf "\033[0;32m Compiling minishell: \033[0;33m$<\033[0m\r"
	@$(CC) $(CFLAGS) -I $(READLINE1) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "\033[0;32m Cleaned\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;32m Fcleaned\033[0m"

re: fclean all
