NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address 
#-------folder-------#
UTILS = utils
LEXER = lexer
HANDLE_ERRORS=handle_errors
EXPANDER=expander
EXECUTION=execution
BUILT_IN=built_in
PIPE=pipe
GC=gc
HEREDOC=heredoc
PASSING=passing
READLINE=$(shell brew --prefix readline)/lib
READLINE1=$(shell brew --prefix readline)/include
#-------files-------#
SRC =minishell.c cleanup.c \
	$(UTILS)/ft_split.c $(UTILS)/ft_strlen.c $(UTILS)/ft_strdup.c $(UTILS)/ft_substr.c $(UTILS)/ft_strjoin.c $(UTILS)/ft_putendl_fd.c $(UTILS)/ft_strtrim.c \
	$(UTILS)/ft_lstsize.c  $(UTILS)/ft_isalnum.c $(UTILS)/ft_itoa.c $(UTILS)/ft_lstlast.c $(UTILS)/ft_split_last_cmd.c $(UTILS)/ft_split_last_cmd_01.c $(UTILS)/ft_strcmp.c\
	$(LEXER)/ft_tonken.c  $(LEXER)/ft_tonken_utils_01.c $(LEXER)/ft_tonken_utils_02.c \
	$(HANDLE_ERRORS)/handle_errors.c $(HANDLE_ERRORS)/handle_errors_utils.c \
	$(EXPANDER)/expander.c $(EXPANDER)/expander_utils01.c $(EXPANDER)/expander_utils02.c \
	$(GC)/ft_free.c  $(GC)/ft_free_env.c $(GC)/ft_close_fds.c $(GC)/ft_free_env_utils_01.c \
	$(EXECUTION)/execution.c $(EXECUTION)/execution_tools.c \
	$(BUILT_IN)/built_in_tools.c $(BUILT_IN)/cd.c $(BUILT_IN)/cd_part2.c $(BUILT_IN)/env.c $(BUILT_IN)/export.c $(BUILT_IN)/pwd.c $(BUILT_IN)/unset.c $(BUILT_IN)/echo.c $(BUILT_IN)/exit.c \
	$(PIPE)/ft_pipe.c sigs/signals.c \
	$(HEREDOC)/ft_headoc.c $(HEREDOC)/ft_heredoc_utils.c \
	$(PASSING)/ft_passing.c $(PASSING)/ft_concatenate.c $(PASSING)/ft_remove_redicrection.c  $(PASSING)/ft_remove_quotes_dlr.c $(PASSING)/ft_passing_utils.c\

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
