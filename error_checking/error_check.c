/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:15:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/19 14:28:0 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error_check.h"

int	print_err(char *preced, int msg_code)
{
	char	*errmsg;

	errmsg = ft_strjoin(ft_strdup("pipex: "), preced);
	if (!errmsg)
		return (0);
	if (msg_code == -1)
		errmsg = ft_strjoin(errmsg, ": command not found\n");
	else if (msg_code == -2)
		errmsg = ft_strjoin(errmsg, ": allocation error\n");
	else if (msg_code == -3)
		errmsg = ft_strjoin(errmsg, ": $PATH var unset\n");
	if (msg_code == 0)
		perror(errmsg);
	else
		write(2, errmsg, ft_strlen(errmsg));
	free(errmsg);
	return (msg_code);
}

int	print_invalid(int bonus)
{
	write(2, "Invalid Format !\n", 17);
	if (bonus)
		write(2, "Use: ./pipex in_file cmd1 .. cmdn out_file\n", 43);
	else
		write(2, "Use: ./pipex in_file cmd1 cmd2 out_file\n", 40);
	return (-1);
}

int	check_file(char *file_path, int access_type)
{
	if (access(file_path, access_type) != 0)
	{
		print_err(file_path, 0);
		return (0);
	}
	return (1);
}

char	*find_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp);
		envp++;
	}
	return (NULL);
}

int	check_cmd(char **cmd, char **envp)
{
	char	*path_var;
	char	***paths[2];

	if (ft_strchr(cmd[0], '/'))
	{
		if (check_file(cmd[0], X_OK))
			return (execve(cmd[0], cmd, envp));
		exit(-1);
	}
	path_var = find_path(envp);
	if (!path_var)
		return (-3);
	paths[0] = ft_split(path_var + 5, ':');
	paths[1] = paths[0];
	if (!paths[0])
		return (-2);
	while (*paths[0])
	{
		*paths[0] = ft_strjoin(ft_strjoin(*paths[0], "/"), cmd[0]);
		if (access(*paths[0], X_OK) == 0)
			if (execve(*paths[0], cmd, envp) == -1)
				return (-1);
		free(*paths[0]++);
	}
	return (free(paths[1]), -1);
}
