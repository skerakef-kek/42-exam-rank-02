#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

typedef struct		s_flags
{
	int		width;
	int		prec;
	int		p;
}				t_flags;

int	g_count;
va_list ap;
t_flags flags;

void	init_flags(void)
{
	flags.width = 0;
	flags.prec = 0;
	flags.p = 0;
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
	g_count++; /*g_count variable holds the return value of ft_printf*/
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


int		num(int n) /*returns length of a decimal number*/
/*
 *	if (n == 0)
 *		len <- len + 1
 *	loop: (n != 0)
 *		n /= 10
 *		len <- len + 1
 *	return (len)
 *	
 */
{
	int len;
	
	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}


int		num_hex(int n) /*return length of a hexadecimal number*/
/*
 *	if (n == 0)
 *		len <- len + 1
 *	loop: (n != 0)
 *		n /= 16
 *		len <- len + 1
 *	return len
 * */
{
	int len;

	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}


int		ft_atoi(const char *s)	/*char* number to int number*/
/*
 *	
 *	loop: (0 <= s <= 9)
 *		num = num * 10 + (*s - 48)
 *		s = (s + 1)
 *	return num
 * */
{
	long num;

	num = 0;
	while (*s >= '0' && *s <= '9')
	{
		num = num * 10 + (*s - 48);
		s++;
	}
	return (num);
}

int		is_num(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
/*return 1 if c is a number, 0 if it's not*/
}

void	print_str()
/*
 *	str <- va_arg (ap, char*)
 *	if (!str)
 *		str = "(null)"
 *	preci <- (flags.p && flags.prec < ft_strlen(str)) ? flags.prec : ft_strlen(str)
 *	spaces <- flags.width - preci
 *	i <- 0
 *	loop: (spaces > 0)
 *		ft_putchar(' ')
 *		spaces--
 *	loop: (i < preci)
 *		ft_putchar(str[i])
 *		i++
 *
 * */
{
	char	*str;
	int i;
	int	preci;
	int	spaces;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	preci = (flags.p && flags.prec < ft_strlen(str)) ? flags.prec : ft_strlen(str);
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

void	ft_puthex(unsigned int n)
/*
 *	num <- "0123456789abcdef"
 *	
 *	if (n < 16)
 *		ft_putchar(num[n])
 *	else
 *		ft_puthex(n / 16)
 *		ft_puthex(n % 16)
 *
 * */
{
	char *num;

	num = "0123456789abcdef";
	if (n < 16)
		ft_putchar(num[n]);
	else if (n > 16)
	{
		ft_puthex(n / 16);
		ft_puthex(n % 16);
	}
}

void	print_hex()
/*
 *	x <- va_arg(ap, unsigned int)
 *	preci <- (flags.prec > num_hex(x) ? flags.prec - num_hex(x) : 0)
 *	spaces <- (preci > 0) ? flags.width - flags.prec : flags.width - num_hex(x)
 *	i <- -1
 *
 *	loop: (++i < spaces)
 *		ft_putchar(' ')
 *	i <- -1
 *	
 *	loop: (++i < preci)
 *		ft_putchar('0')
 *
 *	ft_puthex(x)
 * */
{
	unsigned int x;
	int	preci;
	int spaces;
	int i;

	x = va_arg(ap, unsigned int);
	preci = (flags.prec > num_hex(x) ? flags.prec - num_hex(x) : 0);
	spaces = (preci > 0) ? flags.width - flags.prec : flags.width - num_hex(x);
	i = -1;
	while (++i < spaces)
		ft_putchar(' ');
	i = -1;
	while (++i < preci)
		ft_putchar('0');
	ft_puthex(x);
}


void	ft_putnbr(int n, int preci)
/*
 * if (n < 0)
 * 		ft_putchar('-')
 * 		while (preci)
 *			ft_putchar('0');
 *			preci--;
 * 		i = -n
 *	else 
 *		i = n
 *	while (preci)
 *		ft_putchar('0')
 *		preci--
 *	if (i < 10)
 *		ft_putchar(i + '0')
 *	else if (i > 9)
 *		ft_putnbr(i / 10, preci)
 *		ft_putnbr(i % 10, preci)
 * 	
 *
 * */
{
	unsigned int i;

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
	while (preci)
	{
		ft_putchar('0');
		preci--;
	}
	if (i <= 9)
		ft_putchar(i + '0');
	else if (i >= 10)
	{
		ft_putnbr(i / 10, preci);
		ft_putnbr(i % 10, preci);
	}
}

void	print_int()
/*
 *	d <- va_arg(ap, int)
 *	signe <- (d < 0) ? 1 : 0
 *	preci <- (flags.prec > num(d)) ? flags.prec - num(d) : 0
 *	spaces <- (preci > 0) ? flags.width - (flags.prec + signe) : flags.width - (num(d) + signe)
 *
 *	i <- -1
 *	loop: (++i < spaces)
 *		ft_putchar(' ')
 *	ft_putnbr(d, preci)
 * */
{
	int		d;
	int		signe;
	int		preci;
	int		spaces;
	int		i;

	d = va_arg(ap, int);
	signe = (d < 0) ? 1 : 0;
	preci = (flags.prec > num(d)) ? flags.prec - num(d) : 0 ;
	spaces = (preci > 0) ? flags.width - (flags.prec + signe) : flags.width - (num(d) + signe);
	i = -1;
	while (++i < spaces)
		ft_putchar(' ');
	ft_putnbr(d, preci);
}

void	ft_check(const char *s, int *i)
/*
 *	if (is_num(s[*i]))
 *		flags.width <- ft_atoi(s + (*i))
 *		*i <-  *i + num(flags.width)
 *	
 *	if (s[*i] == '.')
 *		flags.p <-  1
 *		(*i) <- (*i + 1)
 *	
 *	if (is_num(s[*i]))
 *		flags.prec <- ft_atoi(s + (*i))
 *		*i <- *i + num(flags.prec)
 *	
 *	if (s[*i] == 'd')
 *		print_int()
 *	
 *	if (s[*i] == 's')
 *		print_str()
 *
 *	if (s[*i] == 'x')
 *		print_hex()
 *
 * */
{
	if (is_num(s[*i]))
	{
		flags.width = ft_atoi(s + (*i));
		*i += num(flags.width);
	}
	if (s[*i] == '.')
	{
		flags.p = 1;
		(*i)++;
	}
	if (is_num(s[*i]))
	{
		flags.prec = ft_atoi(s + (*i));
		*i += num (flags.prec);
	}
	if (s[*i] == 'd')
		print_int();
	if (s[*i] == 's')
		print_str();
	else if (s[*i] == 'x')
		print_hex();
}

int		ft_printf(const char *s, ...)
/*
 *
 * g_count <- 0
 * va_start(ap, s)
 * i <- 0
 * 
 * loop: (s[i])
 * 		init_flags()
 * 		if (s[i] == '%')
 * 			i <- i + 1
 * 			ft_check(s, &i)
 *		else
 *			ft_putchar(s[i])
 *		i <- i + 1
 *
 *	va_end(ap)
 *	return g_count 
 *
 * */
{
	int i;

	g_count = 0;
	va_start(ap , s);
	i = 0;

	while (s[i])
	{
		init_flags();
		if (s[i] == '%')
		{	
			i++;
			ft_check(s, &i);
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
	ft_printf("%10.2s\n", "TOTO");
	printf("%10.2s\n", "TOTO");
	ft_printf("Magic %s is %7d\n", "number", 42);
	printf("Magic %s is %7d\n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("Hexadecimal for %d is %x\n", 42, 42);
}
