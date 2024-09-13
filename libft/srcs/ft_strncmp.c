/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;
	size_t			i;

	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	if (n == 0)
		return (0);
	if (s1 && !s2)
		return (*s1);
	if (!s1 && s2)
		return (*s2);
	i = 0;
	while (i < n - 1 && s1_uc[i] && s2_uc[i] && s1_uc[i] == s2_uc[i])
		i++;
	return (s1_uc[i] - s2_uc[i]);
}
