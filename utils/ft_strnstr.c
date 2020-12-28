/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:31:27 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 00:08:16 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*check(const char *big, const char *little, size_t size)
{
	char	*start;
	size_t	i;

	start = (char*)big;
	i = 0;
	while (*little)
	{
		if (*big != *little || i == size)
			return (NULL);
		i++;
		big++;
		little++;
	}
	return (start);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*start;
	size_t	i;

	if (!*little)
		return ((char*)big);
	i = 0;
	while (*big && i < len)
	{
		if (*big == *little)
		{
			if ((start = check(big, little, len - i)))
				return (start);
		}
		big++;
		i++;
	}
	return (NULL);
}
