/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-far <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:20:42 by wben-far          #+#    #+#             */
/*   Updated: 2022/04/15 13:05:24 by wben-far         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>

# define ERROR -1
# define EOF_READ 0
# define NO_NL 0
# define NL 1

int	get_len_line(char *line);
int	empty_line(char **line);
int	fill_line_nl(char **line);
int	fill_line(char **line, char *buf);
int	get_next_line(int fd, char **line);

#endif
