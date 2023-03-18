/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:29:07 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/18 17:12:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/utils.h"
#include "include/get_next_line.h"
#include "include/pipe_process.h"
#include "include/error_check.h"

void che()
{
	system("leaks pipex");
}

void	close_pipe(int *pipe, int size)
{
	while (size--)
		close(pipe[size]);
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
	///// TODO : Protect forks and pipe ! (Pids shouldn't be -1)
	///// TODO : Fix when $PATH unset
	///// TODO : cmd not found Error msg
	// //! Remove this
	// if (pid[0] != 0 && pid[1] == 0)
	// 	atexit(che);
	// //!

void	fill_tab(int *tab, int size, int value)
{
	while (size--)
		tab[size] = value;
}

int main(int argc, char **argv, char **envp)
{
	int		pid[2];
	int		pipe_fd[2];

	if (argc != 5)
	{
		write(2, "Invalid Format !\n", 17);
		write(2, "Use: ./pipex in_file cmd1 cmd2 out_file\n", 40);
		return (-1);
	}
	fill_tab(pid, 2, 1);
	if (pipe(pipe_fd) == -1)
		return (print_err("pipe", 0));
	if (!fork_for(pid, 2))
		return (print_err("fork", 0));
	if (IS_CHILD(pid[0]))
		return (cmd_f_in(argv[2], argv[1], pipe_fd, envp));
	else if (IS_CHILD(pid[1]))
		return (cmd_f_out(argv[3], argv[4], pipe_fd, envp));
	close_pipe(pipe_fd, 2);
	wait(NULL);
	wait(NULL);
	return (0);
}
