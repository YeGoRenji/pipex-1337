/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:29:07 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/19 17:14:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/utils.h"
#include "include/get_next_line.h"
#include "include/pipe_process.h"
#include "include/error_check.h"
#include "include/helpers.h"
#include "include/bonus_helpers.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		nb_child;
	int		exit_code;
	int		is_here_doc;

	if (argc < 5)
		return (print_invalid(1), -1);
	is_here_doc = here_doc(&argc, &argv);
	if (is_here_doc == -1)
	{
		unlink("/tmp/here_doc");
		exit(-1);
	}
	nb_child = argc - 3;
	data.pids = (int *)malloc((nb_child) * sizeof(int));
	data.pipes = (int *)malloc(2 * (nb_child - 1) * sizeof(int));
	if (!pipe_for(data.pipes, nb_child) || !fork_for(data.pids, nb_child))
		exit(print_err("fork or pipe", 0));
	exit_code = process_child(data, argv, nb_child, envp);
	if (exit_code != -4)
		exit(exit_code);
	if (is_here_doc)
		unlink("/tmp/here_doc");
	exit(0);
}
