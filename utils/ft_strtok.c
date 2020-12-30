/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:57:58 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 14:35:18 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_chars(char *s, char *delim)
{
	int	chars;
	int	i;

	chars = 0;
	while (s[chars])
	{
		i = 0;
		while (delim[i])
		{
			if (s[chars] == delim[i])
				return (chars);
			i++;
		}
		chars++;
	}
	return (chars);
}

static int	count_parts(char *s, char *delim)
{
	int		parts;
	int		i;

	parts = 1;
	while (*s)
	{
		i = 0;
		while (delim[i])
		{
			if (*s == delim[i])
			{
				parts++;
				break ;
			}
			i++;
		}
		s++;
	}
	return (parts);
}

char		*add_token(char **s, char *delim)
{
	char	*tok;
	int		chars;
	int		j;

	tok = NULL;
	j = 0;
	if (!(chars = count_chars(*s, delim)))
		(*s)++;
	else
	{
		if (!(tok = (char*)malloc(sizeof(char) * (chars + 1))))
			return (NULL);
		while (**s && j < chars)
		{
			tok[j] = **s;
			(*s)++;
			j++;
		}
		tok[j] = '\0';
	}
	return (tok);
}

char		**ft_strtok(char *s, char *delim)
{
	char	**tok;
	int		parts;
	int		chars;
	int		i;

	if (!s || !*s)
		return (NULL);
	parts = count_parts(s, delim);
	if (parts > ft_strlen(s))
		return (NULL);
	if (!(tok = (char**)malloc(sizeof(char*) * (parts + 1))))
		return (NULL);
	i = 0;
	while (i < parts)
	{
		if (s)
		{
			if ((tok[i] = add_token(&s, delim)))
				i++;
		}
		if (!*s)
			break ;
	}
	tok[i] = NULL;
	return (tok);
}
