/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:15:20 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/08 17:45:23 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error_check.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	print_err(char *preced, int msg_code)
{
	char	*errmsg;
	errmsg = ft_strjoin(ft_strdup("pipex: "), preced);
	if (msg_code == -1)
		errmsg = ft_strjoin(errmsg, ": command not found\n");
	else if (msg_code == -2)
		errmsg = ft_strjoin(errmsg, ": allocation error\n");
	else if (msg_code == -3)
		errmsg = ft_strjoin(errmsg, ": $PATH var unset\n");

	if (msg_code == 0)
		perror(errmsg);
	else
		ft_putstr_fd(errmsg, 2);
	free(errmsg);
	return (msg_code);
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
	char	**paths;
	char	**tmp;
	path_var = find_path(envp);
	if (!path_var)
		return (-3);
	paths = ft_split(path_var + 5, ':');
	// paths = NULL;
	tmp = paths;
	if (!paths)
		return (-2);
	while (*paths)
	{
		*paths = ft_strjoin(*paths, "/");
		*paths = ft_strjoin(*paths, cmd[0]);
		// printf("%s : %d\n", *paths, access(*paths, X_OK));
		if (access(*paths, X_OK) == 0)
			execve(*paths, cmd, envp);
		free(*paths);
		paths++;
	}
	free(tmp);
	return (-1);
}
