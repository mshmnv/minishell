/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:38:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/24 13:44:54 by lbagg            ###   ########.fr       */
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
	execute(args, all);
	exit(EXIT_SUCCESS);
}


void	execute_pipe(char **args, t_all *all, t_command **cmds)
{
	pid_t		pid;
	int			not_last;
	int			save_fd;
	int			status;
	int			fd[2];

	not_last = 1;
	int i =0 ;
	
	pipe(fd);

	save_fd = dup(STDIN_FILENO);
	while (i < 2)
	{
		// if ((*cmds)->pipe_flag)
			// pipe(fd);
		// else
			// not_last = 0;
		if ((pid = fork()) < 0)
			error("Failed to fork!");
		else if (pid == 0)
			child_pipe(args, fd, save_fd, all);
		else
			waitpid(pid, &status, WUNTRACED);
		close(save_fd);
		close(fd[1]);
		save_fd = fd[0];
		// if (not_last)
		// {
			if (i == 0)
			{
			(*cmds) = (*cmds)->next;
			free_arr(args);
			args = ft_strtok((*cmds)->command, " \n\t");
			}
		// }
		i++;
	}
	// exit(0);

}



// void	execute_pipe(char **args, t_all *all, t_command **cmds)
// {
// 	pid_t		pid;
// 	int			save_fd;
// 	t_command	*next;
//  	int			status;
// 	char 		**arg2;
	
// 	// while ((*cmds)->pipe_flag)
// 	// {
// 		(*cmds) = (*cmds)->next;

// 		arg2 = ft_strtok((*cmds)->command, " \n\t");
		
// 		pipe(all->fd);

// 		if ((pid = fork()) < 0)
// 			error("Failed to fork!");
// 		else if (pid == 0)  //STDOUT - 1
// 		{
// 			save_fd = dup(STDOUT_FILENO);
// 			close(all->fd[0]);
// 			dup2(all->fd[1], STDOUT_FILENO);    // to write in fd[1]
// 			close(all->fd[1]);
// 			execute(args, all);
// 			dup2(save_fd, STDOUT_FILENO);
// 			close(save_fd);
// 			exit(EXIT_SUCCESS);

// 		}
// 		else
// 		{
// 			save_fd = dup(STDIN_FILENO);
// 			close(all->fd[1]);
// 			dup2(all->fd[0], STDIN_FILENO);  	// to read from fd[0]]
// 			close(all->fd[0]);
// 			execute(arg2, all);
// 			dup2(save_fd, STDIN_FILENO);
// 			close(save_fd);
// 			waitpid(pid, &status, WUNTRACED);
// 		}
// 		close(all->fd[0]);
// 		close(all->fd[1]);
// 	// }
// }