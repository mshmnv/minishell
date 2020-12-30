/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:38:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 19:10:26 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe(char ***args, t_command **cmds)
{
	int			not_last;
	int			save_fd;
	int			fd[2];

	not_last = 1;
	save_fd = dup(STDIN_FILENO);
	while (not_last)
	{
		if ((*cmds)->pipe_flag)
			pipe(fd);
		else
			not_last = 0;
		fork_pipe(save_fd, fd, *args, *cmds);
		save_fd = fd[0];
		if (not_last)
		{
			(*cmds) = (*cmds)->next;
			free_arr(*args);
			*args = ft_strtok((*cmds)->command, " \n\t");
		}
	}
}

void	fork_pipe(int save_fd, int *fd, char **args, t_command *cmds)
{
	pid_t		pid;
	int			status;

	if ((pid = fork()) < 0)
		error(ER_FORK);
	else if (pid == 0)
		child_pipe(args, fd, save_fd, cmds);
	else
		waitpid(pid, &status, WUNTRACED);
	close(save_fd);
	close(fd[1]);
}

void	child_pipe(char **args, int *fd, int save_fd, t_command *cmds)
{
	if (save_fd != STDIN_FILENO)
	{
		dup2(save_fd, STDIN_FILENO);
		close(save_fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (cmds && cmds->redir_flag)
		execute_redirects(args, cmds);
	else
		execute(args);
	exit(EXIT_SUCCESS);
}
