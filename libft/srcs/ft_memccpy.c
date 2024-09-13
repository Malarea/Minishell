/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_uc;
	unsigned char	*src_uc;
	unsigned char	c_uc;
	size_t			i;

	if (!dst || !src)
		return (NULL);
	dst_uc = (unsigned char *)dst;
	src_uc = (unsigned char *)src;
	c_uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dst_uc[i] = src_uc[i];
		if (src_uc[i] == c_uc)
			return (&dst_uc[i + 1]);
		i++;
	}
	return (NULL);
}
