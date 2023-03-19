/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:34:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/19 22:34:39 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/helpers.h"
#include <stdio.h>

void	close_pipe(int *pipe, int size)
{
	while (size--)
		close(pipe[size]);
}

int	is_child(int *pids, int len)
{
	int	nb;

	nb = 1;
	while (len--)
		nb *= pids[len];
	return (nb == 0);
}

void	fill_tab(int *tab, int size, int value)
{
	while (size--)
		tab[size] = value;
}

int	fork_for(int *pids, int nb)
{
	int	i;
	int	len;

	len = nb;
	i = 0;
	if (!pids)
		return (0);
	fill_tab(pids, nb, 1);
	while (i < nb)
	{
		if (!is_child(pids, len))
		{
			pids[i] = fork();
			if (pids[i] == -1)
				return (0);
		}
		if (is_child(pids, len))
			break ;
		i++;
	}
	return (1);
}

int	pipe_for(int *pipe_fds, int nb)
{
	if (!pipe_fds)
		exit(-1);
	while (nb--)
	{
		if (pipe(pipe_fds + 2 * nb) == -1)
			return (0);
	}
	return (1);
}
