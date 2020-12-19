/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 01:55:17 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/18 13:47:57 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *str, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if ((res = (char*)malloc(sizeof(char) * (len + 1))))
	{
		while (str && str[i])
		{
			res[i] = str[i];
			i++;
		}
		while (i <= len)
		{
			res[i] = '\0';
			i++;
		}
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