/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:22:29 by imontero          #+#    #+#             */
/*   Updated: 2023/05/19 19:25:11 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (&((char *)s)[i]);
		i++;
	}
	if (s[i] == (char) c)
		return (&((char *)s)[i]);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i ++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)malloc((1 + len) * sizeof(char));
	if (!sub)
		return (NULL);
	sub[len] = '\0';
	while (s[start] && len > 0)
	{
		len--;
		sub[len] = s[start + len];
	}
	return (sub);
}

char	*ft_getlinelast(char *store)
{
	char	*line;

	line = ft_substr(store, 0, ft_strlen(store));
	free(store);
	store = NULL;
	return (line);
}

char	*ft_getlinenl(char *store)
{
	int		i;
	char	*line;
	char	*temprest1;

	i = 0;
	while (store[i])
	{
		if (store[i] == '\n')
		{
			line = ft_substr(store, 0, i + 1);
			temprest1 = ft_substr(store, i + 1, ft_strlen(store) - i - 1);
			free (store);
			store = NULL;
			store = ft_substr(temprest1, 0, ft_strlen(temprest1));
			free (temprest1);
			temprest1 = NULL;
			return (line);
		}
	i++;
	}
	return (store);
}

void	ft_join(char *store, char *buff, int rd)
{
	char	*temprest;

	buff[rd] = '\0';
	temprest = ft_substr(store, 0, ft_strlen(store));
	free(store);
	store = NULL;
	store = ft_strjoin(temprest, buff);
	free(temprest);
	temprest = NULL;
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
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0)
		{
			free(store);
			store = NULL;
			return (NULL);
		}
		ft_join(store, buff, rd);
	}
	if (ft_strchr(store, '\n'))
		return (ft_getlinenl(store));
	if (store[0] && rd == 0)
		return (ft_getlinelast(store));
	free(store);
	store = NULL;
	return (NULL);
}

int	main(void)
{
	int		fd1;

	char	*gnl1;
	/*char	*gnl2;
	char	*gnl3;
	char	*gnl4;*/
	
	fd1 = open("text3.txt", O_RDONLY);
	
	gnl1 = get_next_line(fd1);
	while(gnl1)
	{
		printf("%s", gnl1);
		free(gnl1);
		gnl1 = get_next_line(fd1);
	}
	free(gnl1);
	gnl1 = get_next_line(fd1);
	printf("%s", gnl1);
	free(gnl1);
	close(fd1);
	return(0);
}
