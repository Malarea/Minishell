/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_needle(size_t i, size_t n, const char *hay, const char *needle)
{
	size_t	j;

	j = 0;
	while (hay[i] == needle[j] && needle[j] && i < n)
	{
		i++;
		j++;
	}
	if (!(needle[j]))
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;

	i = 0;
	if (!haystack && !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	if (needle[0] == '\0' && needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		if (is_needle(i, n, haystack, needle))
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
