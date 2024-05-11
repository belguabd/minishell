/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/11 10:06:27 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>
# include <termios.h>
# include <dirent.h>

# define COLOR_RESET "\x1b[0m"
# define COLOR_GREEN "\x1b[32m"

enum
{
	FREE,
	ALLOC,
	CLOSE,
	OPEN,
};
typedef struct ft_free
{
	void			*add;
	struct ft_free	*next;
}	t_free;
typedef struct s_fd
{
	int			fd;
	struct s_fd	*next;
}	t_fd;
typedef struct t_token_node
{
	int					type;
	char				*value;
	bool				flag;
	int					fd_hrd;
	struct t_token_node	*next;
}	t_token_node;

typedef struct command_node
{
	char				**args;
	int					infile;
	int					outfile;
	bool				isfirst;
	bool				islast;
	t_token_node		*redir;
	struct command_node	*next;
}	t_cmd;
typedef enum tokenize
{
	REDIRECT_APPEND,
	REDIRECT_OUT,
	REDIRECT_IN,
	HEREDOC,
	SPC,
	STRING,
	PIPE,
	DOUBLE_Q,
	SINGLE_Q,
	VAR,	
	EXIT_STATUS,
	DOUBLE_DLR
}	t_token;

typedef struct s_vars
{
	char	**res;
	size_t	i;
	int		j;
	int		flag;
	int		start;
}	t_vars;

typedef struct s_expand
{
	char			*key;
	char			*value;
	bool			isnull;
	bool			isequal;
	bool			ishiden;
	struct s_expand	*next;
}	t_expand;

typedef struct s_export
{
	char	*key;
	char	*value;
	bool	isnull;
	bool	flag;
	int		exit_status;
	int		i;
	int		j;
}	t_export;

char			**ft_split(char const *str, char c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putendl_fd(char *s, int fd);
int				ft_lstsize(t_token_node *lst);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
char			*ft_strjoin_env(char const *s1, char const *s2);
char			*ft_strdup_env(const char *s1);
char			*ft_substr_env(char const *s, unsigned int start, size_t len);
t_expand		*addnew_expand_node_env(char *key, char *value);
void			lstadd_back_expand_env(t_expand **lst, t_expand *new_node);
bool			not_space(char c);
bool			is_space(char c);
int				ft_single_double(t_token_node **head, const char *cmd, int i);
int				ft_dollar(t_token_node **head, const char *cmd, int *i);
int				ft_spaces(t_token_node **head, const char *cmd, int *i);
void			handle_single_quotes(int start, const char *cmd,
					t_token_node **head);
void			handle_double_quotes(int start, const char *cmd,
					t_token_node **head);
void			ft_process_vars(const char *cmd, t_token_node **head, int i);
int				print_error_quote(const char *cmd);
int				quote_error_handling(const char *buffer, size_t *i, char c);
t_token_node	*ft_lstlast(t_token_node *lst);
t_token_node	*tokenization(const char *cmd, t_token_node **head);
t_token_node	*addnew_tkn_node(int token, char *value, int fd);
void			lstadd_back(t_token_node **lst, t_token_node *new);
bool			is_var(char c);
bool			is_string(char c);
int				handle_errors_cmd(t_token_node *head, const char *cmd);
char			*ft_get_var(char *str_var);
char			*get_until_var_exp(char *str_var);
t_token_node	*expand_and_print_vars(t_token_node *head, t_expand *env,
					int exit_status);
char			*get_str_env(t_expand *env, char *str_var);
void			*ft_malloc(size_t size, int status);
void			*ft_malloc_env(size_t size, int status);
char			*ft_substr_env(char const *s, unsigned int start, size_t len);
char			*ft_strdup_env(const char *s1);
t_expand		*addnew_expand_node_env(char *key, char *value);
void			lstadd_back_expand_env(t_expand **lst, t_expand *new_node);
void			*ft_malloc_env(size_t size, int status);
char			*ft_strjoin_env(char const *s1, char const *s2);
void			init_env(t_expand **head, char *env[]);
void			ft_close_fds(int fd, int status);
void			ft_execution(t_cmd *cmd, t_expand **envp,
					int *exit_status);
int				exe_bultin_in_parent(char *cmd[], t_expand **env,
					int *exit_status);
void			ft_execute_bultin(char *cmd[], t_expand **envp,
					int *exit_status);
int				exe_one_cmd_only(t_cmd *cmd, t_expand **env,
					int *exit_status);
char			**get_envp(t_expand *lst_envp);
void			ft_execute_node(char *cmd[], t_expand *envp, char **str_envp,
					int *exit_status);
char			**get_envp(t_expand *lst_envp);
char			**ft_split_last_cmd(char *cmd);
void			ft_putstr_fd(char *s, int fd);
void			handler(int sig);
void			set_cmd_false_true(t_cmd **cmds);
int				*allocat_pids(t_cmd *cmd);
void			init_fds(t_cmd **cmds);
void			pipe_line(t_cmd *cmd, t_expand **env_lst, char *env[],
					int *exit_status);
void			ft_pwd(t_expand *env);
int				ft_cd(char *path, t_expand *env);
void			ft_echo(char **cmd);
void			ft_env(char **cmd, t_expand *envp);
int				ft_unset(char **cmd, t_expand **envp);
int				ft_export(char **cmd, t_expand **envp);
int				pars_key(char *cmd);
int				is_builtin(t_cmd *cmd);
void			get_env_export(t_expand *envp);
int				ft_exit(char **cmd, int exit_status);
void			rm_dbl_q(t_token_node *head);
void			rm_sgl_q(t_token_node *head);
t_token_node	*skip_dr(t_token_node *head);
char			*ft_get_cwd(char *new_path, int mode);
t_expand		*ft_lst_last(t_expand *lst);
void			ft_lst_add_back(t_expand **lst, t_expand *new_node);
int				ft_strcmp(char *s1, char *s2);
void			ft_del_node(t_expand **lst, char *key);
t_expand		*ft_lst_new(char *key, char *val);
void			ft_free_node(t_expand *node);
size_t			ft_lst_size(t_expand *lst);
char			*ft_itoa(int n);
int				is_string_type(int type);
t_cmd			*passing(t_token_node *head);
t_token_node	*rm_redirect(t_token_node *head);
t_token_node	*ft_concatenate(t_token_node *head);
void			process_shell_input(t_token_node **head, const char **cmd,
					int *exit_st, t_expand *env_e);
void			clean_fd_cmd(const char *cmd);
void			clean_exit(const char *cmd, int *exit_st);
void			shell_signal_read(const char **cmd, int *exit_st);
void			ft_heredoc(t_token_node *head, t_expand *env, int *exit_status);
void			ft_sig_handler_her_doc(int sig);
bool			ft_hr_dc_cntrl_c(t_token_node *head);
char			*expand_heredoc(char *cmd, t_expand *env, int exit_status);
int				write_to_file(char *buffer);
bool			is_redirection(int type);
char			*ft_str_exp_double_q(char *str_var, t_expand *env,
					int exit_status);
char			*ft_strtrim(char const *s1, char const *set);
t_cmd			*ft_split_cmd(t_token_node *new_head);	
void			add_new_redir(t_token_node **new, t_token_node *new_head,
					t_token_node **redir);
int				ft_count_cmd(t_token_node *head);
t_cmd			*addnew_cmd(char **args, t_token_node *head_cmd);
void			change_pwd(t_expand **env);
void			change_oldpwd(t_expand **env);
t_expand		*get_oldpwd(t_expand *env);
t_expand		*get_pwd(t_expand *env);
char			*get_home(t_expand *env);
int				red_out(t_token_node *tmp, t_cmd *head);
int				red_append(t_token_node *tmp, t_cmd *head);
int				red_in(t_token_node *tmp, t_cmd *head);
int				red_heredoc(t_token_node *tmp, t_cmd *head);
void			redirection_loop(t_token_node *tmp, t_cmd *head);

void			ft_get_exit_status(int *exit_status,
					int *pid, int i, struct termios *term);
void			ft_cmd_redirection(t_cmd *cmd);
void			ft_piping(t_cmd *cmd, int tmp_fd_in, int *fd);
void			ft_close_cmd_fd(t_cmd *cmd, int *tmp_fd_in, int *fd);
char			*check_path(char **path, char *cmd);
void			ft_change_oldpwd(t_expand *oldpwd, t_expand *env, char *op);
void			ft_change_pwd(t_expand *new_pwd, t_expand *env, char *np);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
