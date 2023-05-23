/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:22:29 by imontero          #+#    #+#             */
/*   Updated: 2023/05/23 12:40:57 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	static	char	*store;
	char			*line;
	char			*temprest;
	int				i;
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
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0)
		{
			free(store);
			store = NULL;
			return (NULL);
		}
		buff[rd] = '\0';
		temprest = ft_substr(store, 0, ft_strlen(store));
		free(store);
		store = NULL;
		store = ft_strjoin(temprest, buff);
		free(temprest);
		temprest = NULL;
	}
	i = 0;
	if (ft_strchr(store, '\n'))
	{	
		while (store[i])
		{
			if (store[i] == '\n')
			{
				line = ft_substr(store, 0, i + 1);
				temprest = ft_substr(store, i + 1, ft_strlen(store) - i - 1);
				free (store);
				store = NULL;
				store = ft_substr(temprest, 0, ft_strlen(temprest));
				free (temprest);
				temprest = NULL;
				return (line);
			}
		i++;	
		}
	}
	if (store[i] && rd == 0)
	{
		line = ft_substr(store, 0, ft_strlen(store));
		free(store);
		store = NULL;
		return (line);
	}
	free(store);
	store = NULL;
	return (NULL);
}
