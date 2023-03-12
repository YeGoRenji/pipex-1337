/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:29:07 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/12 19:44:41 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/utils.h"
#include "include/get_next_line.h"
#include "include/pipe_process.h"
#include "include/error_check.h"

#if 0
void printSPLIT(char **s)
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

void printT(int *tab, int size)
{
    int i = 0;
    printf("[");
    while (i < size)
    {
        if(i != size - 1)
            printf("%d, ",tab[i]);
        else
            printf("%d",tab[i]);
        i++;
    }
    printf("]\n");
}

void printTc(char *tab, int size)
{
    int i = 0;
    printf("[");
    while (i < size)
    {
        if(i != size - 1)
            printf("%c, ",tab[i]);
        else
            printf("%c",tab[i]);
        i++;
    }
    printf("]\n");
}

void che()
{
	system("leaks pipex");
}
#endif

void printTs(char **tab, int size)
{
    int i = 0;
    printf("[");
    while (i < size)
    {
        if(i != size - 1)
            printf("%s, ",tab[i]);
        else
            printf("%s",tab[i]);
        i++;
    }
    printf("]\n");
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

void	pipe_for(int *pipe_fds, int nb)
{
	while (nb--)
		pipe(pipe_fds + 2 * nb);
}

void close_pipe(int *pipe, int size)
{
	while (size--)
		close(pipe[size]);
}

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

void	fill_tab(int *tab, int size, int value)
{
	while (size--)
		tab[size] = value;
}

///// TODO : Fix when $PATH unset
///// TODO : cmd not found Error msg
// //! Remove this
// if (pid[0] != 0 && pid[1] == 0)
// 	atexit(che);
// //!

void	close_every_but(int *pipe_fd, int exception_index, int len)
{
	int	i;
	int	in_index;
	int	out_index;

	in_index = 2 * (exception_index - 1);
	out_index = in_index + 3;
	// printf("in = %d, out = %d\n", in_index, out_index);
	i = 0;
	while (i < len)
	{
		if (i != in_index && i != out_index)
		{
			// printf("Closed %d\n", i);
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

void	here_doc(int *argc, char ***argv)
{
	char	*str;
	int		file_fd;

	if (ft_strncmp((*argv)[1], "here_doc", 9) != 0)
		return ;
	if (*argc != 6)
		return ;
	str = ft_strdup("");
	file_fd = open("/tmp/here_doc", O_WRONLY | O_CREAT, 0644);
	if (file_fd < 0 || !str)
		exit(-1);
	while (1)
	{
		free(str);
		write(1, "pipex here_doc> ", 16);
		str = get_next_line(0);
		if (!str)
		{
			unlink("/tmp/here_doc");
			exit(-1);
		}
		if (ft_strncmp(str, (*argv)[2], ft_strlen((*argv)[2]) + 1) != 0)
		{
			free(str);
			break;
		}
		ft_putstr_fd(file_fd, str);
		str[ft_strlen(str) - 1] = '\0';
	}
	setup_args(argc, argv);
	// printTs(*argv, *argc);
	exit(0);
}

int main(int argc, char **argv, char **envp)
{
	int	*pid;
	int	*pipe_fd;
	int	nb_children;
	int	child_index;
	int	in_index;

	if (argc < 5)
	{
		write(2, "Invalid Format !\n", 17);
		write(2, "Use: ./pipex in_file cmd1 .. cmdn out_file\n", 43);
		return (-1);
	}
	// here_doc(&argc, &argv);
	nb_children = argc - 3;
	pipe_fd = (int *)malloc(2 * (nb_children - 1) * sizeof(int));
	pipe_for(pipe_fd, nb_children - 1);
	pid = (int *)malloc((nb_children) * sizeof(int));
	fill_tab(pid, nb_children, 1);
	if (!fork_for(pid, nb_children))
		return (print_err("fork", 0));
	child_index = get_child_index(pid, nb_children);
	if (child_index != -1)
	{
		// printf("\nI'm child index : %d\n", child_index);
		close_every_but(pipe_fd, child_index, 2 * (nb_children - 1));
		in_index = 2 * (child_index - 1);
		if (child_index == 0)
		{
			// printT(pipe_fd, 2);
			return (cmd_f_in(argv[2], argv[1], pipe_fd, envp));
		}
		else if (child_index == nb_children - 1)
		{
			// printT(pipe_fd + 2 * (nb_children - 2), 2);
			return (cmd_f_out(argv[argc - 2], argv[argc - 1], pipe_fd + 2 * (nb_children - 2), envp));
		}
		else
			return (cmd_pipe(argv[2 + child_index], pipe_fd[in_index], pipe_fd[in_index + 3], envp));
	}
	// //* Parent For Sure !
	free(pid);
	close_pipe(pipe_fd, 2 * (nb_children - 1));
	while (nb_children--)
		wait(NULL);
	// while (1)
	// {
	// 	;
	// }

	// unlink("/tmp/here_doc")
	exit(0);
}
