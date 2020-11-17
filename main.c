/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:23:45 by lbagg             #+#    #+#             */
/*   Updated: 2020/11/16 17:46:10 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_line()
{
	
}

void	sh_loop()
{
	int status;
	char *line;
	char **split;
	
	
	status = 1;
	while (status)
	{
		ft_putstr_fd("shell $> ", 1);
		line = read_line();
		// split line
		// status = execute(split);
		
		free(line);
		// free split
		
	}
}

int		main(int argc, char **argv, char **envp)
{
	sh_loop();
	return (0);
}
