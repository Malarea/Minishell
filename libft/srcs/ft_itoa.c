/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_div(int n)
{
	long	div;

	div = 1;
	while (n / div)
		div *= 10;
	if (n != 0)
		div /= 10;
	return (div);
}

int	get_alloc(int n)
{
	long	div;
	int		to_alloc;

	div = 1;
	to_alloc = 1;
	while (n / div)
	{
		div *= 10;
		to_alloc++;
	}
	return (to_alloc);
}

char	*get_nbr(long div, int n, char *nbr)
{
	long	nb;
	int		i;

	nb = (long)n;
	if (nb < 0)
	{
		nbr[0] = '-';
		nb = -nb;
		i = 1;
	}
	else
		i = 0;
	while (div > 0)
	{
		nbr[i] = nb / div + '0';
		nb -= nb / div * div;
		div /= 10;
		i++;
	}
	nbr[i] = '\0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	long	div;
	int		to_alloc;
	char	*nbr;

	div = get_div(n);
	to_alloc = get_alloc(n);
	nbr = ft_malloc(sizeof(char), to_alloc + 1);
	if (!nbr)
		return (NULL);
	nbr = get_nbr(div, n, nbr);
	return (nbr);
}
