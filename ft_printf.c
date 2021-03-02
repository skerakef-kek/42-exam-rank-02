#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

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
	while (*s)
		i++;
	return (i);
}


int		num(int n); /*returns length of a decimal number*/
/*
 *	if (n == 0)
 *		len <- len + 1
 *	loop: (n != 0)
 *		n /= 10
 *		len <- len + 1
 *	return (len)
 *	
 */



int		num_hex(int n); /*return length of a hexadecimal number*/
/*
 *	if (n == 0)
 *		len <- len + 1
 *	loop: (n != 0)
 *		n /= 16
 *		len <- len + 1
 *	return len
 * */


int		ft_atoi(const char *s);	/*char* number to int number*/
/*
 *	
 *	loop: (0 <= s <= 9)
 *		num = num * 10 + (*s - 48)
 *		s = (s + 1)
 *	return num
 * */

int		is_num(char c);/*return 1 if c is a number, 0 if it's not*/
/*
 *
 *
 * */


void	print_str();
/*
 *
 *
 * */

void	ft_puthex(unsigned int n);
/*
 *
 *
 * */


void	print_hex();
/*
 *
 * */


void	ft_putnbr(int n, int preci);
/*
 *
 * */

void	print_int();
/*
 *
 * */

void	ft_check(const char *s, int i);
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

int		ft_printf(const char *s, ...);
/*
 * int i
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
