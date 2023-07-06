#include "get_next_line.h"

int	ft_strlen_mode(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strldup(char *str, int len)
{
	char	*tmp;
	int		i;

	tmp = (char *)malloc(sizeof(char) * len + 1);
	i = -1;
	while (++i < len)
		tmp[i] = str[i];
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str3;
	int		i;
	int		j;

	if (str2[0] == '\0')
		return (str1);
	str3 = (char *)malloc(sizeof(char) * ft_strlen_mode(str1, '\0') + ft_strlen_mode(str2, '\0') + 1);
	i = -1;
	while (str1[++i])
		str3[i] = str1[i];
	j = 0;
	while (str2[j])
		str3[i++] = str2[j++];
	str3[i] = '\0';
	free(str1);
	return (str3);
}

void	read_all(char **line, int fd)
{
	char	*buff;
	int		rd;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	rd = 1;
	while (rd != 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		buff[rd] = '\0';
		if (!(*line))
			*line = ft_strldup(buff, rd);
		else
			*line = ft_strjoin(*line, buff);
	}
	free(buff);
}

char	*get_next_line(int fd)
{
	static char *head;
	static char	*line;
	char		*new_line;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
	{
		read_all(&line, fd);
		head = line;
	}
	len = ft_strlen_mode(line, '\n');
	if (!len)
	{
		if (head)
		{
			free(head);
			head = NULL;
		}
		return (NULL);
	}
	new_line = ft_strldup(line, len);
	line += len;
	return (new_line);
}

// int	main()
// {
// 	int	fd;
// 	char	*line;
// 	int	i;

// 	// fd = open("buffer.text", O_RDONLY);
// 	fd = open("line.text", O_RDONLY);
// 	// fd = open("em.text", O_RDONLY);
// 	i = 0;
// 	while (i < 15)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line); //1
// 		free(line);
// 		i++;
// 	}
// 	return (0);
// }