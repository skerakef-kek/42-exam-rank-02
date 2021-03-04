#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>


#define HEX 16
#define DEC 10

typedef struct s_flags
{
	int		width;
	int		preci;
	int		p;
}			t_flags;

va_list ap;
t_flags flags;
int	g_count;

void	init_flags()
{
	flags.width = 0;
	flags.preci = 0;
	flags.p = 0;
}

int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}
int		ft_atoi(const char *s)
{
	long num;
	while (*s >= '0' && *s <= '9')
	{
		num = num * 10 + (*s - '0');
		s++;
	}
	return (num);
}

int		is_num(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int		num(int n, int set)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (len != 0)
	{
		n /= set;
		len++;
	}
	return (len);
}

void	ft_puthex(unsigned int x)
{
	char *num;

	num = "0123456789abdef";
	if (x < HEX)
		ft_putchar(num[x]);
	else if (x >= HEX)
	{
		ft_puthex(x / HEX);
		ft_puthex(x % HEX);
	}
}

void	print_hex()
{
	unsigned int x;
	int	preci, spaces, i;
	
	x = va_arg(ap, unsigned int);
	preci = (flags.preci > num(x, HEX))? flags.preci - num(x, HEX) : 0 ;
	spaces = (preci > 0) ? flags.width - flags.preci : flags.width - num(x, HEX);
	i = -1;
	while (++i < spaces)
		ft_putchar(' ');
	i = -1;
	while (++i < preci)
		ft_putchar('0');
	ft_puthex(x);
}

void	print_str()
{
	char *s;
	int preci, spaces, i;

	s = va_arg(ap, char*);
	preci = (flags.p && flags.preci < ft_strlen(s)) ? flags.preci : ft_strlen(s);
	spaces = flags.width - preci;
	i = 0;
	while (spaces > 0)
	{
		ft_putchar(' ');
		spaces--;
	}
	while (i < preci)
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putnbr(int n, int preci)
{
	int i;

	if (n < 0)
	{
		ft_putchar('-');
		while (preci)
		{
			ft_putchar('0');
			preci--;
		}
		i = -n;
	}
	else
		i = n;
	if (i < DEC)
		ft_putchar(i + '0');
	else if (i >= DEC)
	{
		ft_putnbr(i / DEC, preci);
		ft_putnbr(i % DEC, preci);
	}
}

void	print_int()
{
	int d, preci, spaces, signe;

	d = va_arg(ap, int);
	signe = (d < 0) ?  1 : 0;
	preci = (flags.preci < num(d, DEC)) ? (flags.preci - num(d, DEC)) : 0;
	spaces = (preci > 0) ? flags.width - (flags.preci + signe) : flags.width - (num(d, DEC) + signe);
	for (int i = -1; (i < spaces); i++)
		ft_putchar(' ');
	ft_putnbr(d, preci);
}

void	ft_check(const char *s, int *i)
{
	if (is_num(s[*i]))
	{
		flags.width = ft_atoi(s + (*i));
		*i += num(flags.width, DEC);
	}
	if (s[*i] == '.')
	{
		flags.p = 1;
		(*i)++;
	}
	if (is_num(s[*i]))
	{
		flags.preci = ft_atoi(s + (*i));
		*i += num(flags.preci, DEC);
	}
	if (s[*i] == 'd')
		print_int();
	if (s[*i] == 's')
		print_str();
	else if (s[*i] == 'x')
		print_hex();
}

int		ft_printf(const char *s, ...)
{
	int	i;

	i = 0;
	g_count = 0;
	va_start(ap, s);
	while (s[i])
	{
		init_flags();
		if (s[i] == '%')
		{
			ft_check(s, &i);
			i++;
		}
		else
			ft_putchar(s[i]);
		i++;
	}
	va_end(ap);
		
	return (g_count);
}


int		main()
{
	ft_printf("ft_printf: %10.2s\n", "toto");
	printf("printf: %10.2s\n", "toto");
	ft_printf("ft_printf: Magic %s is %5d\n", "number", 42);
	printf("printf: Magic %s is %5di\n", "number", 42);
	ft_printf("ft_printf: Hexadecimal for %d is %x\n", 42, 42);
	printf("printf: Hexadecimal for %d is %x\n", 42, 42);
}
