/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:02:02 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quote_word(t_data *data, int *pos)
{
	char	*quote;
	int		quote_char;

	quote = NULL;
	quote_char = data->str[*pos];
	(*pos)++;
	while (data->str[*pos] && data->str[*pos] != quote_char)
	{
		quote = add_char(data, quote, data->str[*pos]);
		(*pos)++;
	}
	if (data->str[*pos] == quote_char)
		(*pos)++;
	return (quote);
}

char	*get_simple_quote(t_data *data, char *str, int *pos)
{
	char	*quote;

	quote = NULL;
	while (str[*pos] && str[*pos] != '\'')
	{
		quote = add_char(data, quote, str[*pos]);
		(*pos)++;
	}
	if (str[*pos] == '\'')
		(*pos)++;
	return (quote);
}

char	*get_double_quote(t_data *data, char *str, int *pos)
{
	char	*quote;

	quote = NULL;
	while (str[*pos] && str[*pos] != '\"')
	{
		if (str[*pos] == '$')
			quote = concat_str(data, quote, get_var(data, str, pos));
		else
		{
			quote = add_char(data, quote, str[*pos]);
			(*pos)++;
		}
	}
	if (str[*pos] == '\"')
		(*pos)++;
	return (quote);
}

char	*get_quote(t_data *data, char *str, int *pos)
{
	char	*quote;

	if (str[(*pos)++] == '\'')
		quote = get_simple_quote(data, str, pos);
	else
		quote = get_double_quote(data, str, pos);
	return (quote);
}
