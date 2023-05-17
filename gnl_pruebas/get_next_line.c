/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:22:29 by imontero          #+#    #+#             */
/*   Updated: 2023/05/17 18:03:23 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	char	*store;
	size_t	i;
	
	if (fd < 0 || (read(fd, buf, BUFFER_SIZE)) < 0)
		return ;
	read(fd, buf, BUFFER_SIZE);
		
	printf("%s\n", buf);
	
}

int	main(void)
{
	int	fd;
	
	fd = open("text.txt", O_RDONLY);
	printf("%d\n", fd);
	get_next_line(fd);	
	
	close(fd);
	return (0);
}