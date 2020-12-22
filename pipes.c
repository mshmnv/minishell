/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:38:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/22 21:50:20 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// 0 - stdin
// 1 - stdout


void	child_pipe(char **args, t_all *all, int save_fd, int *fd)
{
	if (save_fd != STDIN_FILENO)
	{
		dup2(save_fd, STDIN_FILENO);
		close(save_fd);
	}
	// if (ptr->mass_red[i] != 0)
	// 	pipe_redirect_fork(ptr->mass_red[i], ptr->mass[i], ptr->com_mass[i], ptr);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(args[0], args, NULL);   // why NUll but not envp
	
	exit(EXIT_SUCCESS);
}

void	execute_pipe(char **args, t_all *all, t_command **cmds)
{
	int			fd[2];
	pid_t		pid;
	int			not_last;
	int			save_fd;
	t_command	*next;
	int			status;

	not_last = 1;
	save_fd = dup(STDIN_FILENO);
	while (not_last)
	{
		(*cmds) = (*cmds)->next;
		next = *cmds;
		if (next->pipe_flag)
			pipe(fd);
		else
			not_last = 0;
		if (!(pid = fork()) < 0)
			error("Failed to fork!");
			// errno_error("FORK", errno);
		else if (pid == 0)
		{
			child_pipe(args, all, save_fd, &fd);
			// dup2(all->fd[1], STDOUT_FILENO);  // fd[1] becomes a copy of 1 (stdout)
			// close(all->fd[0]);
			// close(all->fd[1]);
			// execve(args[0], args, all->env_data);
		}
		else
			waitpid(pid, &status, WUNTRACED);
		close(save_fd);
		close(fd[1]);
		save_fd = fd[0];
	}
}
