/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:38:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 00:22:13 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_pipe(char **args, int *fd, int save_fd, t_all *all, t_command *cmds)
{
	if (save_fd != STDIN_FILENO)
	{
		dup2(save_fd, STDIN_FILENO);
		close(save_fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (cmds && cmds->redir_flag)
		execute_redirects(args, cmds, all);
	else
		execute(args, all);
	exit(EXIT_SUCCESS);
}


void	execute_pipe(char ***args, t_all *all, t_command **cmds)
{
	pid_t		pid;
	int			not_last;
	int			save_fd;
	int			status;
	int			fd[2];

	not_last = 1;
	save_fd = dup(STDIN_FILENO);
	while (not_last)
	{
		if ((*cmds)->pipe_flag)
			pipe(fd);
		else
			not_last = 0;
		if ((pid = fork()) < 0)
			error(ER_FORK);
		else if (pid == 0)
			child_pipe(*args, fd, save_fd, all, *cmds);
		else
			waitpid(pid, &status, WUNTRACED);
		close(save_fd);
		close(fd[1]);
		save_fd = fd[0];
		if (not_last)
		{
			(*cmds) = (*cmds)->next;
			free_arr(*args);
			*args = ft_strtok((*cmds)->command, " \n\t");
		}
	}
}
