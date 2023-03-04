/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:41:36 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/03/04 14:52:16 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

static int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

static int	ft_min3(int a, int b, int c)
{
	return (ft_min(ft_min(a, b), c));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	return (ft_memcmp(s1, s2, ft_min3(len_s1 + 1, len_s2 + 1, n)));
}
