/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 01:55:17 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/15 14:03:04 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *str, int len)
{
	char	*res;

	res = NULL;
	if ((res = (char*)malloc(sizeof(char) * (len + 1))))
	{
		ft_memcpy(res, str, ft_strlen(str));
		res[ft_strlen(str)] = '\0';
		free(str);
	} 
	return (res);
}

char	**ft_double_realloc(char **str, int len, char *line)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	if ((res = (char**)malloc(sizeof(char*) * (len + 1))))
	{
		while (str[i])
		{
			res[i] = ft_strdup(str[i]);
			i++;
		}
		res[i] = ft_strdup(line);
		res[i + 1] = NULL;
		free_arr(str);   //it doesn't work in some cases (several coommands)
	}
	return (res);
}