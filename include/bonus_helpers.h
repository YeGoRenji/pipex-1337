/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helpers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:04:16 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/19 14:22:10 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_HELPERS_H
# define BONUS_HELPERS_H

# include "utils.h"
# include "pipe_process.h"
# include "helpers.h"

int		get_child_index(int *pids, int len);
void	close_every_but(int *pipe_fd, int exception_index, int len);
void	setup_args(int *argc, char ***argv);
int		here_doc(int *argc, char ***argv);
int		process_child(t_data data, char **argv, int nb_child, char **envp);

#endif
