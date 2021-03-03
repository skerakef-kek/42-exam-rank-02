#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*str_char(char *str, char buff)
{
	char *ret;
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (len + 2))))
		return (0);
	while (str[i])
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
	char buff;
	int	len;
	int	read_ret;

	buff = -1;
	len = 0;
	if (!(*line = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	while ((read_ret = read(0, &buff, 1) > 0) && buff != '\n')
	{
		*line = str_char(*line, buff);
		len++;
	}
	if (len > 0 && buff != '\n')
		return (-1);
	if (read_ret == 0 && !buff)
		return (0);
	return (1);
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

	return 0;
}
