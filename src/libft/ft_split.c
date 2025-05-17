/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:39:18 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/17 20:54:34 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_words_counter(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static void	ft_free(char **arr, int i)
{
	i--;
	while (i)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	char	*alt_s;

	if (!s)
		return (NULL);
	alt_s = (char *)s;
	arr = malloc((sizeof(char *) * (ft_words_counter(s, c) + 1)));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < ft_words_counter(s, c))
	{
		while (*alt_s == c)
			alt_s++;
		arr[i] = malloc((ft_word_len(alt_s, c) + 1));
		if (arr[i] == NULL)
			return (ft_free(arr, i), NULL);
		ft_strlcpy(arr[i], alt_s, ft_word_len(alt_s, c) + 1);
		alt_s += ft_word_len(alt_s, c);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
