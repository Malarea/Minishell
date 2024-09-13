/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:24:43 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check redirections
*/
int	is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

/*
**	Check quotes
*/
int	check_quote(char *str, int pos)
{
	int	quote_type;

	if (str[pos] != '\'' && str[pos] != '\"')
		return (0);
	quote_type = str[pos++];
	while (str[pos])
	{
		if (str[pos] == quote_type)
			return (1);
		pos++;
	}
	return (0);
}

int	skip_ws(char *str)
{
	int	i;

	i = 0;
	while (ft_is_ws(str[i]))
		i++;
	return (i);
}

char	*add_char(t_data *data, char *str, int c)
{
	char	*new_str;
	int		len_str;
	int		i;

	len_str = ft_strlen(str);
	new_str = malloc(len_str + 2);
	if (!new_str)
		exit_custom(data, NULL, AUTO);
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free_null((void **)&str);
	return (new_str);
}

char	*concat_str(t_data *data, char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	if (!new_str)
		exit_custom(data, NULL, AUTO);
	while (s1 && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free_null((void **)&s1);
	free_null((void **)&s2);
	return (new_str);
}
