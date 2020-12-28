/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:00:49 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/28 14:22:06 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_flags(t_command *cmds)
{
	if (cmds->out_fname)
	{
		if (!cmds->append)
			return(open(cmds->out_fname, O_CREAT | O_WRONLY | O_TRUNC, 0777));
		else
			return(open(cmds->out_fname, O_CREAT | O_WRONLY | O_APPEND, 0777));
	}
	return(open(cmds->in_fname, O_RDONLY));
}

void	execute_redirects(char **args, t_command *cmds, t_all *all)
{
	int fd_file;
	int	fd_tmp;
	int	fd_old;
		
	if ((fd_file = open_flags(cmds)) == -1)
	{
		error(ER_FILE);
		return ;
	}
	if (cmds->out_fname)
	{
		fd_old = dup(STDOUT_FILENO);
		fd_tmp = dup2(fd_file, STDOUT_FILENO);
	}
	else
	{
		fd_old = dup(STDIN_FILENO);
		fd_tmp = dup2(fd_file, STDIN_FILENO);
	}
	if (close(fd_file) == -1 || fd_tmp == -1)
	{
		error(ER_FILE);
		return ;
	}
	execute(args, all);
	if (dup2(fd_old, fd_tmp) == -1 || close(fd_old) == -1)
	{
		error(ER_FILE);
		return ;
	}
}
