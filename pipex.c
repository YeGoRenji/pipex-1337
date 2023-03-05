#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include "include/utils.h"
#include "include/get_next_line.h"


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

void che()
{
	system("leaks pipex");
}

void	pipe_cmd_process(char **cmd, int input_fd, int output_fd, char **envp)
{
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	print_err(cmd[0], check_cmd(cmd, envp));
}

void	fork_for(int *pids, int nb)
{
	int	i;

	i = 0;
	while (i < nb - 1)
	{
		pids[i] = fork();
		pids[i + 1] = -1;
		if (pids[i] != 0)
			pids[i + 1] = fork();
		i++;
	}
}

	// TODO : Protect forks and pipe ! (Pids shouldn't be -1)
	// TODO : Fix when $PATH unset
	///// TODO : cmd not found Error msg
	// //! Remove this
	// if (pid[0] != 0 && pid[1] == 0)
	// 	atexit(che);
	// //!

int main(int argc, char **argv, char **envp)
{
	int file_fd;
	int pid[2];
	char **cmd;
	int pipe_fd[2];
	if (argc != 5)
		return (write(2, "Invalid Format !\nUse: ./pipex in_file cmd1 cmd2 out_file\n", 57));
	pipe(pipe_fd);
	fork_for(pid, 2);
	if (pid[0] == 0)
	{
		close(pipe_fd[0]);
		if (check_file(argv[1], R_OK))
		{
			file_fd = open(argv[1], O_RDONLY);
			cmd = ft_split(argv[2], ' ');
			if (!cmd)
				return (print_err(argv[2], -2));
			pipe_cmd_process(cmd, file_fd, pipe_fd[1], envp);
		}
	}
	else if (pid[1] == 0)
	{
		close(pipe_fd[1]);
		if (access(argv[4], F_OK) || check_file(argv[4], W_OK))
		{
			file_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT);
			cmd = ft_split(argv[3], ' ');
			if (!cmd)
				return (print_err(argv[3], -2));
			pipe_cmd_process(cmd, pipe_fd[0], file_fd, envp);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (pid[0] != 0 && pid[1] != 0)
	{
		wait(NULL);
		wait(NULL);
	}
}
