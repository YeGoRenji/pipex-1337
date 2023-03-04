#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "include/utils.h"
#include <sys/wait.h>

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

int	check_file(char *file_path)
{
	if (access(file_path, R_OK) != 0 || access(file_path, F_OK) != 0)
	{
		write(2, "pipex: ", 7);
		perror(file_path);
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
		return (0);
	paths = ft_split(path_var + 5, ':');
	tmp = paths;
	if (!paths)
		return (0);
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
	return (0);
}

void che()
{
	system("leaks pipex");
}

int main(int argc, char **argv, char **envp)
{
	int ifile_fd;
	int ifile_valid;
	int pid[2];
	char **cmd;
	int fd[2];
	// atexit(che);
	if (argc != 5)
		return (write(2, "Invalid Format ! \nUse: ./pipex file1 cmd1 cmd2 file2\n", 53));

	// TODO : Protect forks and pipe !
	pipe(fd);
	pid[0] = fork();
	pid[1] = -1;
	if (pid[0] != 0)
		pid[1] = fork();
	if (pid[0] == 0)
	{
		close(fd[1]);
		printf("First Child !\n");
		ifile_valid = check_file(argv[1]);
		if (ifile_valid)
		{
			ifile_fd = open(argv[1], O_RDONLY);
			cmd = ft_split(argv[2], ' ');
			// dup2(fd[0], STDOUT_FILENO);
			// close(fd[0]);
			// dup2(ifile_fd, STDIN_FILENO);
			// printf("ALO");
			// close(ifile_fd);
			check_cmd(cmd, envp);
			write(2, "pipex: ", 7);
			perror(cmd[0]);
		}
	} else if (pid[1] == 0)
	{
		close(fd[0]);
		char *str = malloc(5);
		str[4] = '\0';
		printf("Second Child !\n");
		while (read(fd[1], str, 4) != -1)
		{
			puts("Got IT !");
			printf("%s\n", str);
		}
	}
	// char* argvs[] = { "ls", "-la", NULL };
	// execve("ls", argvs, envp);
	// perror(NULL);
	// printf("ALOOO");
	// int fd = open(argv[1], O_RDONLY);

	// printf("fd = %d\n", fd);
	// perror(argv[1]);
	// int pid = fork();
	// if (pid == 0)
	// 	exit(-1);

	if (pid[0] != 0 && pid[1] != 0)
	{
		wait(NULL);
		wait(NULL);
		printf("%d, %d\n", pid[0], pid[1]);
		puts("Salina ~");
	}
	// printf("pid = %d\n", pid);
}
