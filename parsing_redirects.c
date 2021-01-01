/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:22:12 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/01 18:52:24 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_redirects(char redir_symb, char *line, t_command *cmds)
{
	int		j;
	char	*fname;
	int		fstart;

	fstart = 0;
	cmds->redir_flag = 1;
	cmds->append = ((line[fstart] == '>' && line[fstart++]) ? 1 : 0);
	while (line[fstart] == ' ')
		fstart++;
	if (ft_strchr("><", line[fstart]))
	{
		error(ER_SYNTAX);
		return (-1);
	}
	j = 0;
	while (line[fstart + j] && line[fstart + j] != ' ')
		j++;
	if (!(fname = (char*)malloc(sizeof(char) * (j + 1))))
		error(ER_MALLOC);
	ft_strlcpy(fname, line + fstart, j + 1);
	if (redir_symb == '>')
		cmds->out_fname = fname;
	else
		cmds->in_fname = fname;
	return (fstart + j + 1);
}
