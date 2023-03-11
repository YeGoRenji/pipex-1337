/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:29:07 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/11 20:52:31 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/utils.h"
#include "include/get_next_line.h"
#include "include/pipe_process.h"
#include "include/error_check.h"

void printSPLIT(char **s)
{
	int i = 0;
	int j = 0;

	printf("| ");
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			printf("%c", s[i][j]);
			j++;
		}
		printf(" | ");
		i++;
	}
	printf("\n");
}

void printT(int *tab, int size)
{
    int i = 0;
    printf("[");
    while (i < size)
    {
        if(i != size - 1)
            printf("%d, ",tab[i]);
        else
            printf("%d",tab[i]);
        i++;
    }
    printf("]\n");
}

void printTc(char *tab, int size)
{
    int i = 0;
    printf("[");
    while (i < size)
    {
        if(i != size - 1)
            printf("%c, ",tab[i]);
        else
            printf("%c",tab[i]);
        i++;
    }
    printf("]\n");
}

void che()
{
	system("leaks pipex");
}

int is_child(int *pids, int len)
{
	int	nb;

	nb = 1;
	while (len--)
		nb *= pids[len];
	return (nb == 0);
}


int fork_for(int *pids, int nb)
{
	int	i;
	int	len;

	len = nb;
	i = 0;
	while (i < nb)
	{
		if(!is_child(pids, len))
		{
			// printf("Parent ! ");
			// printT(pids, nb);
			pids[i] = fork();
			if (pids[i] == -1)
				return (0);
		}
		if (is_child(pids, len))
		{
			// printf("I'm a child ! ");
			// printT(pids, nb);
			break;
		}
		i++;
	}
	return (1);
}

void	pipe_for(int *pipe_fds, int nb)
{
	while (nb--)
		pipe(pipe_fds + 2 * nb);
}

void close_pipe(int *pipe, int size)
{
	while (size--)
		close(pipe[size]);
}

int	get_child_index(int *pids, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pids[i] == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	fill_tab(int *tab, int size, int value)
{
	while (size--)
		tab[size] = value;
}

///// TODO : Fix when $PATH unset
///// TODO : cmd not found Error msg
// //! Remove this
// if (pid[0] != 0 && pid[1] == 0)
// 	atexit(che);
// //!

void	close_every_but(int *pipe_fd, int exception_index, int len)
{
	int	i;
	int	in_index;
	int	out_index;

	in_index = 2 * (exception_index - 1);
	out_index = in_index + 3;
	// printf("in = %d, out = %d\n", in_index, out_index);
	i = 0;
	while (i < len)
	{
		if (i != in_index && i != out_index)
		{
			// printf("Closed %d\n", i);
			close(pipe_fd[i]);
		}
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	int *pid;
	int *pipe_fd;
	int nb_children;
	nb_children = argc - 3;
	if (argc < 5)
	{
		write(2, "Invalid Format !\n", 17);
		write(2, "Use: ./pipex in_file cmd1 cmd2 out_file\n", 40);
		return (-1);
	}
	pipe_fd = (int *)malloc(2 * (nb_children - 1) * sizeof(int));
	/// TODO : Protect forks and pipe ! (Pids shouldn't be -1)
	// printf("Nbr of children = %d\n", nb_children);
	// printf("Nbr of open fd for pipe = %d\n", 2 * (nb_children - 1));
	pipe_for(pipe_fd, nb_children - 1);
	// if (pipe(pipe_fd) == -1)
	// 	return (print_err("pipe", 0));
	pid = (int *)malloc((nb_children) * sizeof(int));
	fill_tab(pid, nb_children, 1);
	if (!fork_for(pid, nb_children))
		return (print_err("fork", 0));
	int child_index = get_child_index(pid, nb_children);
	if (child_index != -1)
	{
		// printf("I'm child index : %d\n", child_index);
		close_every_but(pipe_fd, child_index, 2 * (nb_children - 1));
		int	in_index = 2* (child_index - 1);
		if (child_index == 0)
			return (cmd_file_pipe(argv[2], argv[1], 1, pipe_fd, envp));
		else if (child_index == nb_children - 1)
			return (cmd_file_pipe(argv[argc - 2], argv[argc - 1], 0, pipe_fd + 2 * (nb_children - 2), envp));
		else
			return (cmd_pipe(argv[2 + child_index], pipe_fd[in_index], pipe_fd[in_index + 3], envp));
	}
	// if (pid[0] == 0)
	// 	return (cmd_file_pipe(argv[2], argv[1], 1, pipe_fd, envp));
	// else if (pid[1] == 0)
	// 	return (cmd_file_pipe(argv[3], argv[4], 0, pipe_fd, envp));
	// free(pid);
	// //* Parent For Sure !
	free(pid);
	close_pipe(pipe_fd, 2 * (nb_children - 1));
	while (nb_children--)
		wait(NULL);
	// wait(NULL);
	// wait(NULL);
	// printf("")
	// while(1);
	return (0);
}
