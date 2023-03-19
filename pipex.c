/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:29:07 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/19 13:46:05 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/utils.h"
#include "include/get_next_line.h"
#include "include/pipe_process.h"
#include "include/error_check.h"
#include "include/helpers.h"

int	main(int argc, char **argv, char **envp)
{
	int		pid[2];
	int		pipe_fd[2];

	if (argc != 5)
	{
		write(2, "Invalid Format !\n", 17);
		write(2, "Use: ./pipex in_file cmd1 cmd2 out_file\n", 40);
		return (-1);
	}
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
