/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:11:33 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/13 12:19:57 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_bin(t_data *data, char *name, char *var_path)
{
	char		*path_bin;
	char		**arr_path;
	struct stat	statbuf;
	int			i;

	path_bin = NULL;
	arr_path = ft_split(var_path, ':');
	if (!arr_path)
		exit_custom(data, NULL, AUTO);
	i = 0;
	while (arr_path[i])
	{
		path_bin = concat_path_bin(data, arr_path[i], name);
		if (stat(path_bin, &statbuf) == SUCCESS)
		{
			ft_free_arr(arr_path);
			return (path_bin);
		}
		free_null((void **)&path_bin);
		i++;
	}
	ft_free_arr(arr_path);
	free_null((void **)&path_bin);
	return (path_bin);
}

char	*get_bin(t_data *data, char *name)
{
	char	*var_path;
	char	*path_bin;

	path_bin = NULL;
	var_path = get_var_path(data);
	if (var_path)
		path_bin = get_path_bin(data, name, var_path);
	free_null((void **)&var_path);
	return (path_bin);
}

char	**get_argv(t_data *data, char **argv)
{
	char		*bin;
	char		*word;

	if (!argv)
		return (NULL);
	if (is_direct_path(data, argv[0]))
		return (argv);
	bin = get_bin(data, argv[0]);
	if (!bin)
	{
		word = ft_strdup(argv[0]);
		ft_free_arr(argv);
		data->status = 127;
		exit_custom(data, word, CUSTOM);
	}
	free_null((void **)&argv[0]);
	argv[0] = bin;
	return (argv);
}
