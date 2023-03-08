/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:29:07 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/08 17:46:48 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/utils.h"
#include "include/get_next_line.h"
#include "include/pipe_process.h"
#include "include/error_check.h"

void printSPLIT(char ** s)
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

void che()
{
	system("leaks pipex");
}

int	fork_for(int *pids, int nb)
{
	int	i;

	i = 0;
	while (i < nb - 1)
	{
		pids[i] = fork();
		printf("%d\n", pids[i]);
		pids[i + 1] = -2;
		if (pids[i] != 0)
		{
			pids[i + 1] = fork();
			printf("%d\n",pids[i + 1]);
		}
		if (pids[i] == -1 || pids[i + 1] == -1)
			return (0);
		i++;
	}
	return (1);
}

void	close_pipe(int *pipe, int size)
{
	while (size--)
		close(pipe[size]);
}

	///// TODO : Protect forks and pipe ! (Pids shouldn't be -1)
	///// TODO : Fix when $PATH unset
	///// TODO : cmd not found Error msg
	// //! Remove this
	// if (pid[0] != 0 && pid[1] == 0)
	// 	atexit(che);
	// //!

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	int		pid[2];
	int		pipe_fd[2];
	if (argc != 5)
	{
		write(2, "Invalid Format !\n", 17);
		write(2, "Use: ./pipex in_file cmd1 cmd2 out_file\n", 40);
		return (-1);
	}
	if (pipe(pipe_fd) == -1)
		// return (print_err("pipe", 0));
	if (!fork_for(pid, 10))
	// 	return (print_err("fork", 0));
	// if (pid[0] == 0)
	// 	return (cmd_file_pipe(argv[2], argv[1], 1, pipe_fd, envp));
	// else if (pid[1] == 0)
	// 	return (cmd_file_pipe(argv[3], argv[4], 0, pipe_fd, envp));
	// //* Parent For Sure !
	// close_pipe(pipe_fd, 2);
	// wait(NULL);
	// wait(NULL);
	return (0);
}
