#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FREE 0
#define ALLOC 1

typedef struct ft_free
{
	void *add;
	struct ft_free *next;
} t_free;
void ft_free_all(t_free *head)
{
	t_free *current = head;
	while (current)
	{
		t_free *next = current->next;
		free(current->add);
		free(current);
		current = next;
	}
	head = NULL; // Reset the head pointer after freeing all memory
}

t_free *addnew_free(void *add)
{
	t_free *new = malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->add = add;
	new->next = NULL;
	return (new);
}
void addback_free(t_free **head, t_free *new)
{
	t_free *tmp = *head;
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
void *ft_malloc(size_t size, int status)
{
	static t_free *head = NULL;
	if (status == ALLOC)
	{
		void *rt = malloc(size);
		if (!rt)
			return (NULL);
		addback_free(&head, addnew_free(rt));
		return (rt);
	}
	else
		ft_free_all(head);
	return (NULL);
}
void f()
{
	system("leaks a.out");
}
int main()
{
	char *str = ft_malloc(10, ALLOC);
	strcpy(str, "Hello");
	printf("%s\n", str);
	ft_malloc(10, FREE);
	atexit(f);
	return (0);
}