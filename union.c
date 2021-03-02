#include <unistd.h>

int		ft_strkchr(char *str, char c, int k)
{
	int i;

	i = 0;
	while (i < k)
	{
		if (str[i] == c)
			return 0;
		i++;
	}
	return 1;
}

int		main(int ac, char **av)
{
	int i, j;

	if (ac == 3)
	{
		i = 0;
		while (av[1][i] != '\0')
		{
			if (ft_strkchr(av[1], av[1][i], i) == 1)
				write (1, &av[1][i], 1);
			i++;
		}
		j = 0;
		while (av[2][j] != '\0')
		{
			if (ft_strkchr(av[2], av[2][j], j) == 1 && ft_strkchr(av[1], av[2][j], i) == 1)
				write(1, &av[2][j], 1);
			j++;
		}
	}
	write (1, "\n", 1);
	return 0;
}
