/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:41:23 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/19 14:21:25 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <unistd.h>
# include <stdlib.h>

void	close_pipe(int *pipe, int size);
int		is_child(int *pids, int len);
void	fill_tab(int *tab, int size, int value);
int		fork_for(int *pids, int nb);
int		pipe_for(int *pipe_fds, int nb);

#endif
