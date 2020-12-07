/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 01:55:17 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/07 22:22:00 by lbagg            ###   ########.fr       */
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

char	**ft_double_realloc(char **str, int len)
{
	char **res;
	int i;

	res = NULL;
	i = 0;
	if ((res = (char**)malloc(sizeof(char*) * (len + 1))))
	{
		while (i < len - 1)
		{
			res[i] = ft_strdup(str[i]);
			i++;
		}
		res[i] = ft_strdup("");
		// free_arr(str);   //it doesn't work in some cases
	}
	return (res);
}