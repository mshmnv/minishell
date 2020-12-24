/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:00:49 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/24 22:48:08 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_flags(t_command *cmds)
{
	if (cmds->out_fname && !cmds->append)
		return (O_CREAT | O_WRONLY);			//O_TRUNC
	if (cmds->out_fname && cmds->append)
		return (O_CREAT | O_WRONLY | O_APPEND);
	else
		return (O_RDONLY);
	
}

void	execute_redirects(char **args, t_command *cmds, t_all *all)
{
	int file;
	int	fd_left;
	int	flags;
		
	flags = open_flags(cmds);
	if (cmds->out_fname)
	{
		file = open(cmds->out_fname, flags);
		fd_left = STDOUT_FILENO;
	}
	else
	{
		file = open(cmds->in_fname, flags);
		fd_left = STDOUT_FILENO;
	}
		
}
