/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/04/27 00:24:11 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/param.h>
#define COLOR_RESET "\x1b[0m"
#define COLOR_GREEN "\x1b[32m"
enum
{
	FREE,
	ALLOC
};
typedef struct ft_free
{
	void *add;
	struct ft_free *next;
} t_free;

typedef struct token_node
{
	int type;
	char *value;
	bool flage;
	struct token_node *next;
} token_node;

typedef struct command_node
{
	char **args;
	int infile;
	int outfile;
	bool isfirst;
	bool islast;
	token_node *redir;
	struct command_node *next;
} t_cmd;

typedef enum tokenize
{
	REDIRECT_APPEND, // >>
	REDIRECT_OUT,	 // >
	REDIRECT_IN,	 // <
	HEREDOC,		 // <<
	SPC,			 //" "
	STRING,			 //"belguabd"
	PIPE,			 //"|"
	DOUBLE_Q,		 //""
	SINGLE_Q,		 //''
	VAR,			 // variable
	EXIT_STATUS,
	DOUBLE_DLR
} t_token;

typedef struct s_vars
{
	char **res;
	size_t i;
	int j;
	int flage;
	int start;
} t_vars;

typedef struct s_expand
{
	char *key;
	char *value;
	struct s_expand *next;
} t_expand;
/*ft_split*/
char **ft_split(char const *str, char c);
size_t ft_strlen(const char *s);

char *ft_strdup(const char *s1);
// char *ft_strdup(const char *cmd, int start, int end);
/*libft*/
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
void ft_putendl_fd(char *s, int fd);
int ft_lstsize(token_node *lst);
int ft_isalnum(int c);
int ft_isdigit(int c);
char *ft_itoa(int n);

/*functions for tokenization */
token_node *ft_lstlast(token_node *lst);
token_node *tokenization(const char *cmd, token_node **head);
token_node *addnew_tkn_node(int token, char *value);
void lstadd_back(token_node **lst, token_node *new);
bool is_var(char c);
bool is_string(char c);
int handle_errors_cmd(token_node *head, const char *cmd);
char *ft_str_exp(char *str_var, t_expand *env);
char *ft_get_var(char *str_var);
char *get_until_var(char *str_var);
token_node *expand_and_print_vars(token_node *head, t_expand *env);
char *get_str_env(t_expand *env, char *str_var);
/*garbage collector*/
void *ft_malloc(size_t size, int status);

// execution
void ft_execution(t_cmd *cmd, t_expand **envp, int *exit_status);
void ft_execute_bultin(char *cmd[], t_expand **envp, int *exit_status);
int exe_bultin_in_parent(char *cmd[], t_expand *env, int *exit_status);
int exe_one_cmd_only(t_cmd *cmd, t_expand *env, int *exit_status);
char **get_envp(t_expand *lst_envp);
void ft_execute_node(char *cmd[], t_expand *envp, char **str_envp, int *exit_status);
<<<<<<< HEAD
char	**get_envp(t_expand *lst_envp);
char	**ft_split_last_cmd(char *cmd);
void	ft_putstr_fd(char *s, int fd);
//signals
void    handler(int sig);

//pipe & fds
void	set_cmd_false_true(t_cmd **cmds);
void    set_fds(t_cmd **cmds);
void    init_fds(t_cmd **cmds);
=======
char **get_envp(t_expand *lst_envp);
char **ft_split_last_cmd(char *cmd);
// signals
void handler(int sig);

// pipe & fds
void set_cmd_false_true(t_cmd **cmds);
void set_fds(t_cmd **cmds);
void init_fds(t_cmd **cmds);
>>>>>>> e295532a2355978aa7cc7f8305041fdae4d96f9b
void pipe_line(t_cmd *cmd, t_expand *env_lst, char *env[], int *exit_status);

// builtin
<<<<<<< HEAD
void 	ft_pwd(t_expand *env);
int	ft_cd(char *path, t_expand *env);
void 	ft_echo(char **cmd);
void 	ft_env(char **cmd, t_expand *envp);
int	ft_unset(char **cmd, t_expand **envp);
int 	ft_export(char **cmd, t_expand **envp);
int		is_builtin(t_cmd *cmd);
void	get_env_export(t_expand *envp);
=======
void ft_pwd();
int ft_cd(char *path, t_expand *env);
void ft_echo(char **cmd);
void ft_env(char **cmd, t_expand *envp);
int ft_unset(char **cmd, t_expand **envp);
int ft_export(char **cmd, t_expand **envp);
int is_builtin(t_cmd *cmd);
void get_env_export(t_expand *envp);
>>>>>>> e295532a2355978aa7cc7f8305041fdae4d96f9b
void ft_exit(char **cmd);
// tools

t_expand *ft_lst_last(t_expand *lst);
void ft_lst_add_back(t_expand **lst, t_expand *new_node);
int ft_strcmp(char *s1, char *s2);
void ft_del_node(t_expand **lst, char *key);
t_expand *ft_lst_new(char *key, char *val);
void ft_free_node(t_expand *node);
size_t ft_lst_size(t_expand *lst);
char *ft_itoa(int n);

// static int allocationCount = 0;

// static inline void* __malloc(size_t size, char *file, int line)
// {
// 	void* ptr = NULL;
// 	if (!ft_strcmp(file, "gc/ft_free.c") && line == 30)
// 	{
// 		if (allocationCount >= 3)
// 			return NULL;
// 		allocationCount++;
// 		ptr = malloc(size);
// 	}
// 	else
// 		ptr = malloc(size);
// 	return ptr;
// }

// #ifndef malloc
// #define malloc(size) __malloc(size, __FILE__, __LINE__)
// #endif

#endif
