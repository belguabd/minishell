NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address 
#-------folder-------#
UTILS = utils
LEXER = lexer
ERRORS=errors
EXPANDER=expander
EXECUTION=execution
BUILT_IN=built_in
PIPE=pipe
GC=gc
HEREDOC=heredoc
PASSING=passing
SRC=src
BUILD=build
READLINE=$(shell brew --prefix readline)/lib
READLINE1=$(shell brew --prefix readline)/include
#-------files-------#
SRC_F =main.c \
	$(SRC)/$(UTILS)/ft_split.c $(SRC)/$(UTILS)/cleanup.c $(SRC)/$(UTILS)/ft_strlen.c \
	$(SRC)/$(UTILS)/ft_strdup.c $(SRC)/$(UTILS)/ft_substr.c $(SRC)/$(UTILS)/ft_strjoin.c \
	$(SRC)/$(UTILS)/ft_putendl_fd.c $(SRC)/$(UTILS)/ft_strtrim.c \
	$(SRC)/$(UTILS)/ft_lstsize.c  $(SRC)/$(UTILS)/ft_isalnum.c \
	$(SRC)/$(UTILS)/ft_itoa.c $(SRC)/$(UTILS)/ft_lstlast.c $(SRC)/$(UTILS)/ft_split_last_cmd.c \
	$(SRC)/$(UTILS)/ft_split_last_cmd_01.c $(SRC)/$(UTILS)/ft_strcmp.c\
	$(SRC)/$(LEXER)/ft_tonken.c  $(SRC)/$(LEXER)/ft_tonken_utils_01.c $(SRC)/$(LEXER)/ft_tonken_utils_02.c \
	$(ERRORS)/handle_errors.c $(ERRORS)/handle_errors_utils.c \
	$(SRC)/$(EXPANDER)/expander.c $(SRC)/$(EXPANDER)/expander_utils01.c $(SRC)/$(EXPANDER)/expander_utils02.c \
	$(BUILD)/$(GC)/ft_free.c  $(BUILD)/$(GC)/ft_free_env.c \
	$(BUILD)/$(GC)/ft_close_fds.c $(BUILD)/$(GC)/ft_free_env_utils_01.c \
	$(SRC)/$(EXECUTION)/execution.c $(SRC)/$(EXECUTION)/execution2.c \
	$(SRC)/$(EXECUTION)/execution3.c $(SRC)/$(EXECUTION)/execution_tools.c \
	$(SRC)/$(BUILT_IN)/built_in_tools.c $(SRC)/$(BUILT_IN)/cd.c \
	$(SRC)/$(BUILT_IN)/cd_part2.c $(SRC)/$(BUILT_IN)/cd_part3.c\
	$(SRC)/$(BUILT_IN)/env.c $(SRC)/$(BUILT_IN)/export.c \
	$(SRC)/$(BUILT_IN)/export2.c $(SRC)/$(BUILT_IN)/pwd.c \
	$(SRC)/$(BUILT_IN)/unset.c $(SRC)/$(BUILT_IN)/echo.c $(SRC)/$(BUILT_IN)/exit.c \
	$(BUILD)/$(PIPE)/ft_pipe.c $(BUILD)/$(PIPE)/ft_pipe2.c \
	$(BUILD)/$(PIPE)/pipes_tools.c $(BUILD)/$(PIPE)/redirection.c $(BUILD)/sigs/signals.c \
	$(BUILD)/$(HEREDOC)/ft_headoc.c $(BUILD)/$(HEREDOC)/ft_heredoc_utils.c \
	$(SRC)/$(PASSING)/ft_passing.c $(SRC)/$(PASSING)/ft_concatenate.c \
	$(SRC)/$(PASSING)/ft_remove_redicrection.c  $(SRC)/$(PASSING)/ft_remove_quotes_dlr.c \
	$(SRC)/$(PASSING)/ft_passing_utils.c\

OBJ = $(SRC_F:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -L $(READLINE) -I $(READLINE1) -o $(NAME)
	@echo "\033[0;32m Minishell compiled\033[0m"

%.o: %.c include/minishell.h
	@printf "\033[0;32m Compiling minishell: \033[0;33m$<\033[0m\r"
	@$(CC) $(CFLAGS) -I $(READLINE1) -c $< -o $@
clean:
	@rm -rf $(OBJ)
	@echo "\033[0;32m Cleaned\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;32m Fcleaned\033[0m"

re: fclean all
