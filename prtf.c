#include <unistd.h>
#include <stdarg>


#define HEX 16
#define DEC 10

typedef struct s_flags
{
	int		width;
	int		preci;
	int		p
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

int		ft_atoi(char *s)
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

void	print_hex()
{
	unsigned int x;
	int	preci, spaces, i;
	
	x = va_arg(ap, unsigned int);
	preci = (flags.prec > num(x, HEX))? flags.prec - num(x, HEX) : 0 ;
	spaces = (preci > 0) ? flags.width - flags.prec : flags.width - num(x, HEX);
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

	s = va_arg(ap, char*)
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
		ft_putchar(str[i]);
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
	if (i < 10)
		ft_putchar(i + '0');
	else if (i > 9)
	{
		ft_putnbr(i / 10);
		ft_putnbr(i % 10);
	}
}

void	print_int()
{
	int d, preci, spaces, signe;

	d = va_arg(ap, int);
	signe = (d < 0) 1 : 0;
	preci = (flag.prec < num(d, DEC)) ? (flag.prec - num(d, DEC)) : 0;
	spaces = (preci > 0) ? flags.width - (flags.prec + signe) : flags.width - (num(d, DEC) + signe);
	for (i = -1; (i < spaces); i++)
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
	if (s[*i] == d)
		print_int();
	if (s[*i] == s)
		print_str();
	else if (s[*i] == x)
		print_hex();
}

int		ft_printf(const char *s, ...)
{
	int	i;

	i = 0;
	va_start(ap, s);
	while (s[i])
	{
		init_flags();
		if (s[i] == '%')
		{
			ft_check(s, &i);
			i++
		}
		else
			ft_putchar(s[i]);
		i++;
	}
	va_end(ap)
		
	return (g_count);
}

