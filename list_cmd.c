/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 01:50:26 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 14:42:28 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_cmd_list(void)
{
	t_command	*cmds;

	cmds = NULL;
	if ((cmds = (t_command*)malloc(sizeof(t_command))))
	{
		cmds->command = NULL;
		cmds->pipe_flag = 0;
		cmds->redir_flag = 0;
		cmds->in_fname = NULL;
		cmds->out_fname = NULL;
		cmds->append = 0;
		cmds->file = -1;
		cmds->next = NULL;
	}
	else
		error(ER_MALLOC);
	return (cmds);
}

void		free_cmd_list(t_command **cmds)
{
	t_command	*next;

	while (*cmds)
	{
		next = (*cmds)->next;
		free((*cmds)->command);
		free((*cmds)->in_fname);
		free((*cmds)->out_fname);
		free(*cmds);
		*cmds = next;
	}
}
