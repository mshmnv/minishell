/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:41:59 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 13:35:45 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_pwd(char **args, char **env_data)
{
	char	*cwd;
	
	ft_putendl_fd((cwd = getcwd(NULL, 0)), 1);
	free(cwd);
	return (env_data);
}
