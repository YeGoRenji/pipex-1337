/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:11:05 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/08 17:11:35 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	ft_free_split(char **split_ptr)
{
	char **ptr;

	if (!split_ptr)
		return ;
	ptr = split_ptr;
	while(*ptr)
		free(*ptr++);
	free(split_ptr);
}
