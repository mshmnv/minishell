/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:45:38 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/25 13:25:43 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int error)
{
	if (error == ER_FORK)
		error_errno();
	else if (error == ER_EXECUTE)
		ft_putendl_fd("shell: Failed to execute", 1);
}

void	error_errno()
{
	char	*massege;
	
	g_error = errno;
	massege = strerror(errno);
	ft_putstr_fd("shell: ", 1);
	ft_putendl_fd(massege, 1);	
}

void	error_no_cmd(char *arg)
{
	g_error = 127;
	ft_putstr_fd("shell: ", 1);
	ft_putstr_fd(arg, 1);
	ft_putendl_fd(": command not found", 1);
}

void	error_exit(char *arg)
{
	ft_putstr_fd("shell: exit: ", 1);
	ft_putstr_fd(arg, 1);
	ft_putendl_fd(": numeric argument required", 1);
	exit(255);
}