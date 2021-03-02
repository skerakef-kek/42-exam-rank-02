#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;	
	return (i);
}

char	*ft_charjoin(char *str, char buff)
{
	int len;
	int i;
	char *ret;

	len = ft_strlen(str);
	i = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (len + 2))))
		return (0);
	while (str[i] != '\0')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = buff;
	ret[i + 1] = '\0';
	free(str);
	str = NULL;
	return (ret);
}

int		get_next_line(char **line)
{
	int	read_ret;
	char	buff;
	int		len;

	len = 0;
	buff = -1;
	if (!(*line = (char *)malloc(sizeof(char) * 1)))
		return -1;
	*line[0] = '\0';
	while ((read_ret = read(0, &buff, 1) > 0) && buff != '\n')
	{
		*line = ft_charjoin(*line, buff);
		len++;
	}
	if (len > 0 && buff != '\n')
		return -1;
	if (read_ret == 0 && !buff)
		return 0;
	return 1;
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
