/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strssplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 02:45:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/10/02 19:28:50 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_word_len(char const *s, char const *charset)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && ft_strchr(charset, s[len]) == NULL)
		len++;
	return (len);
}

static size_t	ft_count_words(char const *s, char const *charset)
{
	size_t	words;

	words = 0;
	while (*s != '\0')
	{
		if (ft_strchr(charset, *s) != NULL)
			s++;
		else
		{
			words++;
			s += ft_word_len(s, charset);
		}
	}
	return (words);
}

char			**ft_strssplit(char const *s, char const *charset)
{
	size_t	words;
	char	**tab;
	size_t	i;
	size_t	word_len;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, charset);
	if (!(tab = (char **)malloc(sizeof(*tab) * (words + 1))))
		return (NULL);
	tab[words] = 0;
	i = 0;
	while (i < words)
	{
		while (ft_strchr(charset, *s) != NULL)
			s++;
		word_len = ft_word_len(s, charset);
		if (!(tab[i] = ft_strsub(s, 0, word_len)))
			return (ft_strtab_free(tab));
		s += word_len;
		i++;
	}
	return (tab);
}
