/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soujaour <soujaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:20:52 by soujaour          #+#    #+#             */
/*   Updated: 2025/05/17 20:53:44 by soujaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_strlen(const char *s)
{
	ssize_t	len;

	len = 0;
	if (s == NULL)
		return (len);
	while (s && s[len])
		len++;
	return (len);
}
