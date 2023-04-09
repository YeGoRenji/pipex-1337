/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:53:44 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/04/09 12:30:19 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_PROCESS_H
# define PIPE_PROCESS_H

# include "utils.h"
# include <fcntl.h>

# define FLAGS_INPUT O_RDONLY
# define FLAGS_OUTPUT O_WRONLY | O_TRUNC | O_CREAT
# define FLAGS_BONUS O_WRONLY | O_APPEND | O_CREAT

int	cmd_pipe(char *cmd, int input_fd, int output_fd, char **envp);
int	cmd_f_in(char *cmd, char *file_path, int *pipe_fd, char **envp);
int	cmd_f_out(char *cmd, char *file_path, int *pipe_fd, char **envp);
#endif
