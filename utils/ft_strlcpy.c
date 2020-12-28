/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:35:25 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 00:08:03 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;

	if (!dst || !src)
		return (0);
	srclen = ft_strlen(src);
	if (size != 0)
	{
		if (srclen >= size)
		{
			ft_memcpy(dst, src, size - 1);
			dst[size - 1] = '\0';
		}
		else
			ft_memcpy(dst, src, srclen + 1);
	}
	return (srclen);
}
