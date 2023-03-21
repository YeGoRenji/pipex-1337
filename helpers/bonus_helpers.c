/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:33:14 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/21 12:55:37 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus_helpers.h"

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

void	close_every_but(int *pipe_fd, int exception_index, int len)
{
	int	i;
	int	in_index;
	int	out_index;

	in_index = 2 * (exception_index - 1);
	out_index = in_index + 3;
	i = 0;
	while (i < len)
	{
		if (i != in_index && i != out_index)
		{
			close(pipe_fd[i]);
		}
		i++;
	}
}

void	setup_args(int *argc, char ***argv)
{
	int	i;

	(*argv)[1] = "/tmp/here_doc";
	i = 2;
	while (i < *argc - 1)
	{
		(*argv)[i] = (*argv)[i + 1];
		i++;
	}
	*argc = *argc - 1;
}

int	here_doc(int *argc, char ***argv)
{
	char	*str;
	int		file_fd;

	if (ft_strncmp((*argv)[1], "here_doc", 9) != 0 || *argc < 6)
		return (0);
	str = ft_strdup("");
	file_fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0 || !str)
		return (-1);
	while (1)
	{
		free(str);
		write(1, "pipex> ", 7);
		str = get_next_line(0);
		if (!str)
			return (-1);
		str[ft_strlen(str) - 1] = '\0';
		if (ft_strncmp(str, (*argv)[2], ft_strlen((*argv)[2]) + 1) == 0)
			break ;
		ft_putstr_fd(file_fd, str, 1);
	}
	setup_args(argc, argv);
	close(file_fd);
	return (1);
}


#include <errno.h>

int	process_child(t_data data, char **argv, int nb_child, char **envp)
{
	int	in_ind;
	int	child_ind;

	child_ind = get_child_index(data.pids, nb_child);
	if (child_ind != -1)
	{
		close_every_but(data.pipes, child_ind, 2 * (nb_child - 1));
		in_ind = 2 * (child_ind - 1);
		if (child_ind == 0)
			return (cmd_f_in(argv[2], argv[1], data.pipes, envp));
		else if (child_ind == nb_child - 1)
			return (cmd_f_out(argv[nb_child + 1], argv[nb_child + 2],
					data.pipes + 2 * (child_ind - 1), envp));
		else
			return (cmd_pipe(argv[2 + child_ind],
					data.pipes[in_ind], data.pipes[in_ind + 3], envp));
	}
	free(data.pids);
	close_pipe(data.pipes, 2 * (nb_child - 1));
	free(data.pipes);
	while (nb_child--)
		wait(NULL);
	return (-4);
}
