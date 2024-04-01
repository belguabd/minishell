/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:00:39 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/01 20:36:29 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **get_envp(t_expand *lst_envp)
{
	t_expand *head = lst_envp;
	size_t size;
	char **envp;
	int i;

	i = 0;
	size = ft_lst_size(lst_envp);
	if (size == 0)
		return (NULL);
	envp = (char **)malloc((size + 1) * sizeof(char *));
	if (!envp)
		perror("malloc");
	while (head)
	{
		// TO_DO:ft_strjoin fail case
		envp[i] = ft_strjoin(head->key, "=");
		envp[i] = ft_strjoin(envp[i], head->value);
		i++;
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	ft_execution(t_cmd *cmd, t_expand **envp)
{
	char **env;
	// if(!cmd || !cmd->args || !*cmd->args)
	// 	return ;

	env = get_envp(*envp);
	set_cmd_false_true(&cmd);
	pipe_line(cmd, *envp, env);
}

// }

void ft_execute_bultin(char *cmd[], t_expand **envp)
{
	if(!cmd || !*cmd)
		return ;
	if(ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "/bin/echo") == 0)
	{
		ft_echo(cmd);
		exit(0);
	}
	if(ft_strcmp(cmd[0], "export") == 0)
	{
		ft_export(cmd, envp);
		exit(0) ;
	}
	if(ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "/usr/bin/env") == 0)
	{
		ft_env(cmd, *envp);
		exit(0);
	}
	if(ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "/usr/bin/cd") == 0)
	{
		ft_cd(cmd[1]);
		exit(0);
	}
	if(ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "/bin/pwd") == 0)
	{
		ft_pwd();
		exit(0);
	}
	if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_unset(cmd, envp);
		exit(0);
	}
}

char	*check_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if(cmd[0]== '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (path[i])
	{
		cmd_path = ft_strjoin("/", cmd);
		cmd_path = ft_strjoin(path[i], cmd_path);
		if(access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
		//free(cmd_path);
		cmd_path = NULL;
	}
	return (cmd);
}

void ft_execute_node(char *cmd[], t_expand *envp, char **str_envp)
{
	char **paths = NULL;
	char *new_cmd;

	ft_execute_bultin(cmd, &envp);
	while (envp)
	{
		if (ft_strcmp(envp->key, "PATH") == 0)
			break ;
		envp = envp->next;
	}
	if (envp)
		paths = ft_split(envp->value, ':');
	new_cmd = check_path(paths, cmd[0]);
	if(!new_cmd)
	{
		perror(cmd[0]);
		exit(0);
	}
	execve(new_cmd, cmd, str_envp);
	perror(cmd[0]);
}

// int main()
// {
// 	t_expand *envp = NULL;
// 	char *cmd1[] = {"cat", NULL};
// 	char *cmd2[] = {"cat", NULL};
// 	char *cmd3[] = {"wc","-l" , NULL};
	
// 	ft_lst_add_back(&envp, ft_lst_new(ft_strdup("var1"), ft_strdup("jkanf")));
// 	ft_lst_add_back(&envp, ft_lst_new(ft_strdup("PATH"), ft_strdup("/Users/soel-bou/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/soel-bou/.brew/bin")));
// 	ft_lst_add_back(&envp, ft_lst_new(ft_strdup("var3"), ft_strdup("jkanf")));

// 	token_node *token = (token_node*)malloc(sizeof(token_node));
// 	token_node *token2 = (token_node*)malloc(sizeof(token_node));
// 	token_node *token3 = (token_node*)malloc(sizeof(token_node));
//     token->type = REDIRECT_IN;
//     token->value = "file";
//     token->next = NULL;

// 	token2->type = REDIRECT_IN;
//     token2->value = "file2";
//     token2->next = token3;
	
// 	token3->type = REDIRECT_APPEND;
//     token3->value = "file3";
//     token3->next = NULL;
	
//     t_cmd *head = (t_cmd *)malloc(sizeof(t_cmd));
// 	t_cmd *head2 = (t_cmd *)malloc(sizeof(t_cmd));
// 	t_cmd *head3 = (t_cmd *)malloc(sizeof(t_cmd));
	
//     head->args = cmd1;
// 	head->redir = token;
//     head->next =head3;

// 	head2->args = cmd2;
// 	head2->outfile = 1;
// 	head2->infile = 0;
// 	head2->redir = NULL;
//     head2->next = head3;

// 	head3->args = cmd3;
//     head3->next = NULL;
// 	head3->redir = NULL;
	

// 	ft_execution(head, &envp);
// 	// pid_t pid = getpid();

//     // // Create a buffer to hold the command
//     // char command[100];
    
//     // // Construct the command with the PID
//     // snprintf(command, sizeof(command), "lsof -p %d", (int)pid);

//     // // Execute the command
//     // system(command);
// }