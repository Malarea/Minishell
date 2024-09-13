/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_uc;
	unsigned char	c_uc;
	size_t			i;

	if (!s)
		return (NULL);
	s_uc = (unsigned char *)s;
	c_uc = (unsigned char)c;
	if (c_uc == 0 && n > ft_strlen((char *)s_uc))
		return (&s_uc[ft_strlen((char *)s_uc)]);
	i = 0;
	while (i < n)
	{
		if (s_uc[i] == c_uc)
			return (&s_uc[i]);
		i++;
	}
	return (NULL);
}
