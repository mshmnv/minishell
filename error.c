/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:45:38 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 13:53:59 by student          ###   ########.fr       */
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
		ft_putendl_fd("shell: Allocation failed", STDERR_FILENO);
	else if (error == ER_FILE)
	{
		g_exit = 1;
		error_errno();
	}
	else if (error == ER_SYNTAX)
	{
		g_exit = 258;
		ft_putendl_fd("shell: Syntax error", STDERR_FILENO);
	}
}

void	error_errno(void)
{
	char	*massege;

	massege = strerror(errno);
	ft_putstr_fd("shell: ", STDERR_FILENO);
	ft_putendl_fd(massege, STDERR_FILENO);
}

void	error_no_cmd(char *arg)
{
	g_exit = 127;
	ft_putstr_fd("shell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	if (ft_strchr(arg, '/'))
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else
		ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	error_exit(char *arg)
{
	ft_putstr_fd("shell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(255);
}

void	error_cd(char *arg)
{
	g_exit = 1;
	if (arg)
	{
		ft_putstr_fd("shell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory ", STDERR_FILENO);
	}
	else
		ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
}
