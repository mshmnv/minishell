/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:38:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/22 13:14:43 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// 0 - stdin
// 1 - stdout

void	execute_pipe(char **args, t_all *all, int pipe_before)
{
	pid_t	pid;
	int		status;

	pipe(all->fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(all->fd[1], STDOUT_FILENO);  // fd[1] becomes a copy of 1 (stdout)
		close(all->fd[0]);
		close(all->fd[1]);
		execve(args[0], args, all->env_data);
	}
	else if (pid < 0)
		error("Failed to fork!");
		// errno_error("FORK", errno);
	else
		waitpid(pid, &status, WUNTRACED);
}