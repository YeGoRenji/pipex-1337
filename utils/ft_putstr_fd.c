/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:48:47 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/12 16:56:22 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/utils.h"

void	ft_putstr_fd(int fd, char *str)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}
