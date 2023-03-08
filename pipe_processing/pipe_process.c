/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:52:21 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/08 17:45:48 by ylyoussf         ###   ########.fr       */
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
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	err_code = print_err(cmd_split[0], check_cmd(cmd_split, envp));
	ft_free_split(cmd_split);
	return (err_code);
}

int	cmd_file_pipe(char *cmd, char *file_path, int is_input, int* pipe_fd, char **envp)
{
	int	file_fd;

	if (is_input && !check_file(file_path, R_OK))
		return (-1);
	if (!is_input && !(access(file_path, F_OK) || check_file(file_path, W_OK)))
		return (-1);
	file_fd = open(file_path, IF_LINE(is_input, FLAGS_INPUT, FLAGS_OUTPUT));
	if (file_fd == -1)
		return (print_err(file_path, 0));
	if (is_input)
	{
		close(pipe_fd[0]);
		return (cmd_pipe(cmd, file_fd, pipe_fd[1], envp));
	}
	else
	{
		close(pipe_fd[1]);
		return (cmd_pipe(cmd, pipe_fd[0], file_fd, envp));
	}
}
