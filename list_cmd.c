/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 01:50:26 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/01 14:27:31 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_cmd_list(void)
{
	t_command	*cmds;

	cmds = NULL;
	if ((cmds = (t_command*)malloc(sizeof(t_command))))
	{
		if (!(cmds->args = (char**)malloc(sizeof(char*) * 2)))
			error(ER_MALLOC);
		else
		{
			cmds->args[0] = NULL;
			cmds->args[1] = NULL;
		}
		cmds->args_size = 1;
		cmds->pipe_flag = 0;
		cmds->redir_flag = 0;
		cmds->in_fname = NULL;
		cmds->out_fname = NULL;
		cmds->append = 0;
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
		if ((*cmds)->args)
			free_arr((*cmds)->args);
		if ((*cmds)->in_fname)
			free((*cmds)->in_fname);
		if ((*cmds)->out_fname)
			free((*cmds)->out_fname);
		free(*cmds);
		*cmds = next;
	}
}
