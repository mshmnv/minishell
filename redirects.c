/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:00:49 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 17:00:07 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_flags(t_command *cmds, int std)
{
	if (std == 1)
	{
		if (!cmds->append)
			return(open(cmds->out_fname, O_CREAT | O_WRONLY | O_TRUNC, 0777));
		else
			return(open(cmds->out_fname, O_CREAT | O_WRONLY | O_APPEND, 0777));
	}
	return(open(cmds->in_fname, O_RDONLY));
}

int		fd_dup(int fd_std, int file, int *fd_linkstd)
{
	int	fd_tmp;

	*fd_linkstd = dup(fd_std);
	fd_tmp = dup2(file, fd_std);
	if (close(file) == -1 || fd_tmp == -1)
		return (-1);
	return (fd_tmp);
}

void	execute_redirects(char **args, t_command *cmds, t_all *all)
{
	int fd_filein;
	int fd_fileout;
	int	fd_stdin;
	int	fd_stdout;
		
	if (cmds->out_fname)
	{
		if ((fd_fileout = open_flags(cmds, 1)) == -1)
			return (error(ER_FILE));
		if ((fd_fileout = fd_dup(STDOUT_FILENO, fd_fileout, &fd_stdout)) == -1)
			return (error(ER_FILE));
	}
	if (cmds->in_fname)
	{
		if ((fd_filein = open_flags(cmds, 0)) == -1)
			return (error(ER_FILE));
		if ((fd_filein = fd_dup(STDIN_FILENO, fd_filein, &fd_stdin)) == -1)
			return (error(ER_FILE));
	}
	execute(args, all);
	if (cmds->out_fname)
		if (dup2(fd_stdout, fd_fileout) == -1 || close(fd_stdout) == -1)
			return (error(ER_FILE));
	if (cmds->in_fname)
		if (dup2(fd_stdin, fd_filein) == -1 || close(fd_stdin) == -1)
			return (error(ER_FILE));
}
