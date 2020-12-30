/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:42:36 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 20:57:58 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exit(char **args)
{
	int	i;
	int	j;

	ft_putendl_fd("exit", 1);
	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		exit(EXIT_SUCCESS);
	j = 0;
	if (args[1][j] == '-' || args[1][j] == '+')
		j++;
	while (args[1][j])
	{
		if (!ft_isdigit(args[1][j]))
			error_exit(args[1]);
		j++;
	}
	if (i == 2)
		exit(ft_atoi(args[1]) % 256);
	else
		ft_putendl_fd("shell: exit: too many arguments", STDERR_FILENO);
}
