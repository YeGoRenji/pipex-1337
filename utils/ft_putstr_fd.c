/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:48:47 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/19 13:55:44 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	ft_putstr_fd(int fd, char *str, int newline)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
	if (newline)
		write(fd, "\n", 1);
}
