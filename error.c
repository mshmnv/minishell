/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:45:38 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 12:48:49 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int error)
{
	if (error == ER_FORK)
		error_errno();
	else if (error == ER_EXECUTE)
	{
		g_exit = 126;
		error_errno();
	}
	else if (error == ER_MALLOC)
		ft_putendl_fd("shell: Allocation failed", 1);
	else if (error == ER_FILE)
	{		
		g_exit = 1;
		error_errno();
	}
	else if (error == ER_SYNTAX)
	{
		g_exit = 258;
		ft_putendl_fd("shell: Syntax error", 1);
	}
}

void	error_errno(void)
{
	char	*massege;

	massege = strerror(errno);
	ft_putstr_fd("shell: ", 1);
	ft_putendl_fd(massege, 1);
}

void	error_no_cmd(char *arg)
{
	g_exit = 127;
	ft_putstr_fd("shell: ", 1);
	ft_putstr_fd(arg, 1);
	if (ft_strchr(arg, '/'))
		ft_putendl_fd(": No such file or directory", 1);
	else
		ft_putendl_fd(": command not found", 1);
}

void	error_exit(char *arg)
{
	ft_putstr_fd("shell: exit: ", 1);
	ft_putstr_fd(arg, 1);
	ft_putendl_fd(": numeric argument required", 1);
	exit(255);
}

void	error_cd(char *arg)
{
	g_exit = 1;
	if (arg)
	{
		ft_putstr_fd("shell: cd: ", 1);
		ft_putstr_fd(arg, 1);
		ft_putendl_fd(": No such file or directory ", 1);
	}
	else
		ft_putendl_fd("bash: cd: HOME not set", 1);
}
