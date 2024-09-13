/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;
	unsigned char	i;

	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	if (n == 0)
		return (0);
	if (s1 && !s2)
		return (*s1_uc);
	if (!s1 && s2)
		return (*s2_uc);
	i = 0;
	while (i < (n - 1) && s1_uc[i] == s2_uc[i])
		i++;
	return (s1_uc[i] - s2_uc[i]);
}
