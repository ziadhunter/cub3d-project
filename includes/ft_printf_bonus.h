/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:50:56 by rabounou          #+#    #+#             */
/*   Updated: 2025/12/19 12:19:28 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <libft.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_opt
{
	int		width;
	int		pad;
	int		alt;
	char	leading_space_sign;
	int		fill;
	int		precision[2];
}			t_opt;

typedef struct s_func
{
	char	flag;
	int		(*f)(va_list, t_opt *);
}			t_func;

int			ft_printf(const char *str, ...);

int			ft_putchar(int c);
int			ft_isdigit(int c);
int			char_in_chaset(char c, char *set);
int			writer(int *count, char *s, int slen);
char		*convert(char *result, int sign_space, unsigned long n, char *base);
void		calculate_width_precision(char *s, t_opt *opt, int *slen,
				int *sign);

/*Printing funtions*/
int			ft_putnbr(char *s, t_opt *opt);
int			ft_putstr(char *s, t_opt *opt);
int			ft_putaddr(char *s, t_opt *opt);

/*Printing functions (width/precision)*/
int			print_all(int *count, t_opt *opt, char *s, int slen);
int			print_all_2(t_opt *opt, char *s, int slen, int sign);

/*Handle format specifiers*/
int			print_mod(va_list args, t_opt *opt);
int			print_precision(int *count, int precision);
int			print_hex_cap(va_list args, t_opt *opt);
int			print_udec(va_list args, t_opt *opt);
int			print_dec(va_list args, t_opt *opt);
int			print_hex(va_list args, t_opt *opt);
int			print_addr(va_list args, t_opt *opt);
int			print_str(va_list args, t_opt *opt);
int			print_char(va_list args, t_opt *opt);

/*Flags handling functions*/
int			ft_atoi_s(const char *str, int *i);
void		init_options(t_opt *opt);
int			print_filler(int *count, char c, int cond, int n);
void		get_options(const char *s, int *i, t_opt *opt);

#endif
