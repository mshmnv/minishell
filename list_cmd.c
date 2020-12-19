/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 01:50:26 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/19 14:19:49 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_cmd_list()
{
	t_command	*cmds;

	cmds = NULL;
	if ((cmds = (t_command*)malloc(sizeof(t_command))))
	{
		cmds->command = NULL;
		cmds->pipe_flag = 0;
		cmds->redir_flag = 0;
		cmds->redir_filename = NULL;
		cmds->next = NULL;
	}
	return (cmds);
}

void	free_cmd_list(t_command **cmds)
{
	t_command	*next;

	while (*cmds)
	{
		next = (*cmds)->next;
		free((*cmds)->command);
		free((*cmds)->redir_filename);
		free(*cmds);
		*cmds = next;
	}
}
