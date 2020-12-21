/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:38:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/21 10:36:37 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**execute_pipe(char **args, t_all *all, char **env_data)
{
	// int		fd[2];
	// pid_t	pid;
	// int		tmp_0_fd = dup(0);

	
	// pid = fork();
	// if (pid == 0)
	// {
	// 	dup2(all->fd[1], 1);  // fd[1] becomes a copy of 1 (stdout)
	// 	close(all->fd[0]);
	// 	execve(args[0], args, env_data);
	// 	close(fd[1]);
	// }
	// else if (pid < 0)
	// 	error("Failed to fork!");
	// else
	// 	wait(&pid);
	return (env_data);
}