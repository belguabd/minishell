/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:27:32 by belguabd          #+#    #+#             */
/*   Updated: 2024/04/17 11:27:43 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_fd
{
    int fd;
    struct s_fd *next;
} t_fd;

t_fd *add_new_fd(int fd)
{
    t_fd *new = malloc(sizeof(t_fd));
    if (!new)
        return (NULL);
    new->fd = fd;
    new->next = NULL;
    return (new);
}

void add_back_fd(t_fd **head, t_fd *new)
{
    t_fd *tmp = *head;
    if (!tmp)
    {
        *head = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
void ft_close_fds(int fd, int status)
{
    static t_fd *head = NULL;
    if (status == OPEN)
        add_back_fd(&head, add_new_fd(fd));
    if (status == CLOSE)
    {
        t_fd *current = head;
        while (current)
        {
            t_fd *next = current->next;
            close(current->fd);
            free(current);
            current = next;
        }
        head = NULL;
    }
}
