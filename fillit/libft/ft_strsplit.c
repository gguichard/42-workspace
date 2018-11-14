/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 02:45:25 by gguichar          #+#    #+#             */
/*   Updated: 2018/08/10 03:06:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			words++;
			s += ft_word_len(s, c);
		}
	}
	return (words);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	words;
	char	**tab;
	size_t	i;
	size_t	word_len;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * (words + 1))))
		return (NULL);
	tab[words] = 0;
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		word_len = ft_word_len(s, c);
		if (!(tab[i] = ft_strsub(s, 0, word_len)))
			return (NULL);
		s += word_len;
		i++;
	}
	return (tab);
}
