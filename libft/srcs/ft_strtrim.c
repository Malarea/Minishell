/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:21:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_empty(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!is_set(s1[i], set))
			return (0);
		i++;
	}
	return (1);
}

/*
** to_trim_start
*/
int	t_s(char const *s1, char const *set)
{
	int	to_trim;
	int	index;

	to_trim = 0;
	index = 0;
	while (s1[index] && is_set(s1[index], set))
	{
		to_trim++;
		index++;
	}
	return (to_trim);
}

/*
** to_trim_end
*/
int	t_e(char const *s1, char const *set)
{
	int	to_trim;
	int	index;

	to_trim = 0;
	index = ft_strlen(s1) - 1;
	while (index >= 0 && is_set(s1[index], set))
	{
		to_trim++;
		index--;
	}
	return (to_trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		end;
	int		index;
	int		i;

	if (!s1 || !set)
		return (NULL);
	if (check_empty(s1, set))
	{
		str = ft_malloc(sizeof(char), 1);
		if (!str)
			return (NULL);
		*str = '\0';
		return (str);
	}
	str = ft_malloc(1, ft_strlen(s1) - t_s(s1, set) - t_e(s1, set) + 1);
	if (!str)
		return (NULL);
	end = ft_strlen(s1) - t_e(s1, set);
	index = t_s(s1, set);
	i = 0;
	while (index < end)
		str[i++] = s1[index++];
	str[i] = '\0';
	return (str);
}
