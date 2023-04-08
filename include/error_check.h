/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:15:28 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/04/08 14:51:25 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CHECK_H
# define ERROR_CHECK_H

# include "utils.h"

int		print_err(char *preced, int msg_code);
int		check_file(char *file_path, int access_type);
char	*find_path(char **envp);
int		check_cmd(char **cmd, char **envp);
int	print_invalid(int bonus);
#endif
