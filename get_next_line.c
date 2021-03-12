#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

size_t	ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}
char	*ft_strjoin(char *line, char buffer)
{
	char *str;
	int i = ft_strlen(line);

	if (!(str = (char *)malloc(i + 2)))
		return (0);
	i = 0;
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	str[i] = buffer;
	str[i + 1] = '\0';
	free(line);
	line = NULL;
	return (str);
}

int		get_next_line(char **line)
{
	char *buffer;
	int		n;

	buffer = (char *)malloc(2);
	if (!line || !buffer || !(*line = (char *)malloc(1)))
		return (-1);
	*line[0] = '\0';
	while ((n = read(0, buffer, 1)) > 0)
	{
		if (buffer[0] == '\n')
			break ;
		*line = ft_strjoin(*line, buffer[0]);
	}
	free(buffer);
	buffer = NULL;
	return (n);
}

int		main()
{
	char *line;
	while (get_next_line(&line) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s\n", line);
	free(line);
	line = NULL;

	return (0);
}
