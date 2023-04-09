/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:29:07 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/04/09 13:24:51 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/utils.h"
#include "include/get_next_line.h"
#include "include/pipe_process.h"
#include "include/error_check.h"
#include "include/helpers.h"
#include "include/bonus_helpers.h"

static void	edit_envp(char **envp, int is_here_doc)
{
	char	**tmp;
	char	*str;

	tmp = envp;
	while (*tmp++)
		;
	if (is_here_doc)
		str = ft_strdup("HERE_DOC=1");
	else
		str = ft_strdup("HERE_DOC=0");
	if (!str)
		return ;
	*(tmp - 1) = str;
	*tmp = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		nb_child;
	int		exit_code;
	int		is_here_doc;

	if (argc < 5)
		return (print_invalid(1));
	is_here_doc = here_doc(&argc, &argv);
	edit_envp(envp, is_here_doc);
	if (is_here_doc == -1)
	{
		unlink("/tmp/here_doc");
		exit(-1);
	}
	nb_child = argc - 3;
	data.pids = (int *)malloc((nb_child) * sizeof(int));
	data.pipes = (int *)malloc(2 * (nb_child - 1) * sizeof(int));
	if (!pipe_for(data.pipes, nb_child - 1) || !fork_for(data.pids, nb_child))
		exit(print_err("fork or pipe", 0));
	exit_code = process_child(data, argv, nb_child, envp);
	if (exit_code != -4)
		exit(exit_code);
	if (is_here_doc)
		unlink("/tmp/here_doc");
	printf("LAAAAAAAAAAAA");
	exit(0);
}
