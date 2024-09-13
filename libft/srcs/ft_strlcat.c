/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	output;
	size_t	i;
	size_t	j;

	if (!dst || !src)
		return (0);
	if (dstsize < ft_strlen(dst))
		output = ft_strlen(src) + dstsize;
	else
		output = ft_strlen(src) + ft_strlen(dst);
	if (dstsize > 0 && dstsize - 1 > ft_strlen(dst))
	{
		i = 0;
		while (dst[i] != '\0')
			i++;
		j = 0;
		while (src[j] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[j];
			j++;
			i++;
		}
		dst[i] = '\0';
	}
	return (output);
}
