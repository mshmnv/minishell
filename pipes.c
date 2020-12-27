/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:38:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/27 18:02:23 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// do_command
// command == builtins ? builtin
// commnad == > ? redirect_command
// command == $? ? curr_err_command(1)
// else external_command

//fork_ran = execute_process



// 0 - stdin
// 1 - stdout

// void	redirect_pipe(char **args, t_all *all, int file)
// {
// 	pid_t	pid;
// 	int		fd[2];
// 	int		status;

// 	pipe(fd);
// 	if ((pid = fork()) < 0)
// 	{
// 		// errno_error("FORK", errno);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		dup2(file, fd[1]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		if (args != NULL)
// 			execve(args[0], args, all->env_data);
// 		// else
// 			// do_commnad(com_mass, ptr);
// 		close(fd[1]);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 		waitpid(pid, &status, WUNTRACED);
// }

void	child_pipe(char **args, int *fd, int save_fd, t_all *all)
{
	if (save_fd != STDIN_FILENO)
	{
		dup2(save_fd, STDIN_FILENO);
		close(save_fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	// if (cmds->redir_flag)
		// pipe_redirect();
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
			child_pipe(*args, fd, save_fd, all);
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
