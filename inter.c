#include <unistd.h>
#include <stdio.h>

int		ft_strkchr(char *s, char c, int k)
{
	int i;

	i = 0;
	while (i < k)
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int		main(int ac, char **av)
{
	int i, j;
	
	if (ac == 3)
	{
		i = 0;
		while (av[1][i] != '\0')
		{
			j = 0;
			while (av[2][j] != '\0')
			{
				if (av[1][i] == av[2][j] && ft_strkchr(av[1], av[1][i], i) == 1)
				{	
					write(1, &av[1][i], 1);
					break;
				}
			//	printf ("av[1][%d] == av[2][%d] : %c == %c",i, j, av[1][i], av[2][j]);
			//	printf("|| ft_strkchr (av[1], av[1][%d], %d) : %d\n", i, i,ft_strkchr(av[1], av[1][i], i));
				j++;
			}
			//printf ("\n");
			i++;
		}
	}
	write(1, "\n", 1);
	return 0;
}
