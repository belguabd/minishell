/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:50:21 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/20 09:19:13 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/param.h>
#define COLOR_RESET "\x1b[0m"
#define COLOR_GREEN "\x1b[32m"

typedef struct command_node
{
	char **args;
	int input;
	int ouput;
	struct command_node *next;
} t_cmd;

typedef enum tokenize
{
	REDIRECT_APPEND, // >>
	REDIRECT_OUT,	 // >
	REDIRECT_IN,	 // <
	HEREDOC,		 // <<
	SPACE,			 //" "
	STRING,			 //"belguabd"
	PIPE,			 //"|"
	DOUBLE_Q,		 //""
	SINGLE_Q,		 //''
	VAR,			 // variable
	EXIT_STATUS
} t_token;
typedef struct token_node
{
	t_token type;
	char *value;
	struct token_node *next;
} token_node;

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
int	ft_isalnum(int c);
int	ft_isdigit(int c);





//execution

//builtin
void	ft_pwd();
void    ft_cd(char *path);
void	ft_echo(char **cmd);
void	ft_env(char **cmd, t_expand *envp);
void	ft_unset(char **cmd, t_expand **envp);
void	ft_export(char **cmd, t_expand **envp);

//tools

t_expand	*ft_lstlast(t_expand *lst);
void		ft_lst_add_back(t_expand **lst, t_expand *new_node);
int			ft_strcmp(char *s1, char *s2);
void		ft_del_node(t_expand **lst, char *key);
t_expand	*ft_lst_new(char *key, char *val);
void		ft_free_node(t_expand *node);

#endif