/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:38:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/21 15:47:25 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// 0 - stdin
// 1 - stdout
void	execute_pipe(char **args, t_all *all, int pipe_before)
{
	// pid_t	pid;
	// // int		tmp_0_fd = dup(0);

	// pid = fork();
	// if (pipe_before)
	// {
	// 	dup2(all->fd[0], 0);
	// }
	// else
	// {
	// 	if (pid == 0)
	// 	{
	// 		dup2(all->fd[1], 1);  // fd[1] becomes a copy of 1 (stdout)
	// 		close(all->fd[0]);
	// 		execve(args[0], args, all->env_data);
	// 		close(all->fd[1]);
	// 	}
	// 	else if (pid < 0)
	// 		error("Failed to fork!");
	// 	else
	// 		wait(&pid);
	// }
}