/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:22:29 by imontero          #+#    #+#             */
/*   Updated: 2023/05/24 16:55:29 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getlinelast(char **store)
{
	char	*line;

	line = ft_substr(*store, 0, ft_strlen(*store));
	free(*store);
	*store = NULL;
	return (line);
}

char	*ft_getlinenl(char **store)
{
	int		i;
	char	*line;
	char	*temprest1;

	i = 0;
	while ((*store)[i])
	{
		if ((*store)[i] == '\n')
		{
			line = ft_substr(*store, 0, i + 1);
			temprest1 = ft_substr(*store, i + 1, ft_strlen(*store) - i - 1);
			free (*store);
			*store = NULL;
			*store = ft_substr(temprest1, 0, ft_strlen(temprest1));
			free (temprest1);
			temprest1 = NULL;
			return (line);
		}
	i++;
	}
	return (*store);
}

char	*ft_join(char **store, char *buff, ssize_t *rd, int fd)
{
	char	*temprest;

	*rd = read(fd, buff, BUFFER_SIZE);
	if (*rd < 0)
	{
		free(*store);
		*store = NULL;
		return (NULL);
	}
	buff[*rd] = '\0';
	temprest = ft_substr(*store, 0, ft_strlen(*store));
	free(*store);
	*store = NULL;
	*store = ft_strjoin(temprest, buff);
	free(temprest);
	temprest = NULL;
	return (*store);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*store;
	ssize_t			rd;

	if (!store)
	{
		store = malloc(1);
		*store = '\0';
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rd = 1;
	while (ft_strchr(store, '\n') == NULL && rd != 0)
	{
		store = ft_join(&store, buff, &rd, fd);
		if (store == NULL)
			return (NULL);
	}
	if (ft_strchr(store, '\n'))
		return (ft_getlinenl(&store));
	if (store[0] && rd == 0)
		return (ft_getlinelast(&store));
	free(store);
	store = NULL;
	return (NULL);
}
