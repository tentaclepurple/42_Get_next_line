#include "get_next_line.h"

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

int	main(void)
{
	int	fd;
	char	*buf[BUFFER_SIZE];
	int	rd = 0;
	
	fd = open("text3.txt", O_RDONLY);
	//printf("%d\n", fd);
	rd = read(fd, buf, BUFFER_SIZE);
	printf("%d\n", rd);
	rd = read(fd, buf, BUFFER_SIZE);
	printf("%d\n", rd);
	rd = read(fd, buf, BUFFER_SIZE);
	printf("%d\n", rd);
	rd = read(fd, buf, BUFFER_SIZE);
	printf("%d\n", rd);
	rd = read(fd, buf, BUFFER_SIZE);
	printf("%d\n", rd);
	rd = read(fd, buf, BUFFER_SIZE);
	printf("%d\n", rd);
	close(fd);
	return (0);

/*	char	*a = "";
	char	*b = "hello";*/
		
	return (0);
}