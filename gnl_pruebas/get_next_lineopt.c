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
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3
#endif

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
	sub = (char *)malloc(1 + len * sizeof(char));
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
		if (!store)
			return (NULL);
		*store = '\0';
	}
		
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rd = 1;
	while (ft_strchr(store, '\n') == NULL && rd != 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		buff[rd] = '\0';
		store = ft_strjoin(temprest, buff);
	}
	i = 0;
	if (ft_strchr(store, '\n'))
	{	
		while (store[i])
		{
			if (store[i] == '\n')
			{
				line = ft_substr(store, 0, i + 1);
				temprest = ft_substr(store, i + 1, ft_strlen(store) - i + 1);
				free (store);
				store = ft_substr(temprest, 0, ft_strlen(temprest));
				free (temprest);
				return (line);
			}
		i++;	
		}
	}
	if (store[i] && rd == 0)
	{
		line = ft_substr(store, 0, ft_strlen(store));
		free(store);
		return (line);
	}
	return (NULL);
}

int	main(void)
{
	/*int		fd1;
	int		fd2;*/
	int		fd;

	char	*gnl1;
	char	*gnl2;
	char	*gnl3;
	char	*gnl4;
	
	/*fd1 = open("text3.txt", O_RDONLY);
	
	gnl1 = get_next_line(fd1);
	while(gnl1)
	{
		printf("%s", gnl1);
		free(gnl1);
		gnl1 = get_next_line(fd);
	}
	free(gnl1);

	printf("\n----\n");

	close(fd);*/
/*
	fd1 = open("text3.txt", O_RDONLY);
	gnl1 = get_next_line(fd1);
	printf("%s", gnl1);
	free(gnl1);

	//close(fd);

	fd2 = open("text1.txt", O_RDONLY);
	gnl1 = get_next_line(fd2);
	printf("%s", gnl1);
	free(gnl1);

	//fd1 = open("text3.txt", O_RDONLY);
	gnl1 = get_next_line(fd1);
	printf("%s", gnl1);
	free(gnl1);

	close(fd1);
	close(fd2);
*/
	fd = open("text3.txt", O_RDONLY);
	gnl1 = get_next_line(fd);	
	printf("Linea 1: %s", gnl1);
	free(gnl1);
	gnl2 = get_next_line(fd);
	printf("Linea 2: %s", gnl2);
	free(gnl2);
	gnl3 = get_next_line(fd);
	printf("Linea 3: %s", gnl3);
	gnl4 = get_next_line(fd);	
	printf("Linea 4: %s", gnl4);	
	free(gnl4);	
	close(fd);
	//system("leaks a.out");
	return (0);
}
