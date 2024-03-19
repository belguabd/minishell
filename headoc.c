#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
int ft_strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
bool is_exp(char *dlmtr)
{
	int i = 0;
	while (dlmtr[i])
	{
		if (dlmtr[i] == '\"' || dlmtr[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}
int main(int ac, char *av[])
{
	// static int i;
	// char *str = join ("file_", itoa(i));

	int fd = open("tmp.txt", O_CREAT | O_RDWR, 0777);
	while (1)
	{
		char *text = readline("> ");
		// av[1] = "\"stop\"";
		// if (is_exp(av[1]))
		// {
		write(fd, text, strlen(text));
		write(fd, "\n", 1);
		// }
		// else
		// {
		// 	// puts("KO");
		// 	write(fd, text, strlen(text));
		// 	write(fd, "\n", 1);
		// }

		if (!ft_strcmp(av[1], text))
			break;
	}

	return 0;
}