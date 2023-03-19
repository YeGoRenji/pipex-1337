/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:52:21 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/19 22:21:42 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipe_process.h"
#include "../include/error_check.h"

int	cmd_pipe(char *cmd, int input_fd, int output_fd, char **envp)
{
	char	**cmd_split;
	char	err_code;

	cmd_split = ft_split(cmd, ' ');
	if (!cmd_split)
		return (print_err(cmd, -2));
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (print_err(cmd, 0));
	close(input_fd);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return (print_err(cmd, 0));
	close(output_fd);
	err_code = print_err(cmd_split[0], check_cmd(cmd_split, envp));
	ft_free_split(cmd_split);
	return (err_code);
}

int	cmd_f_out(char *cmd, char *file_path, int *pipe_fd, char **envp)
{
	int	file_fd;

	close(pipe_fd[1]);
	if (!(access(file_path, F_OK) || check_file(file_path, W_OK)))
		return (-1);
	file_fd = open(file_path, FLAGS_OUTPUT, 0644);
	if (file_fd == -1)
		return (print_err(file_path, 0));
	return (cmd_pipe(cmd, pipe_fd[0], file_fd, envp));
}

int	cmd_f_in(char *cmd, char *file_path, int *pipe_fd, char **envp)
{
	int	file_fd;

	close(pipe_fd[0]);
	if (!check_file(file_path, R_OK))
		return (-1);
	file_fd = open(file_path, FLAGS_INPUT);
	if (file_fd == -1)
		return (print_err(file_path, 0));
	return (cmd_pipe(cmd, file_fd, pipe_fd[1], envp));
}
