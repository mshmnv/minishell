/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:41:59 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/16 11:31:15 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_pwd(char **args, char **env_data)
{
	char	*cwd;
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
		ft_putendl_fd("pwd: too many arguments", 1);
	else if (i == 1)
	{
		ft_putendl_fd((cwd = getcwd(NULL, 0)), 1);
		free(cwd);
	}
	return (env_data);
}
