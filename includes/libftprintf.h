/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 10:50:04 by stestein          #+#    #+#             */
/*   Updated: 2018/06/05 16:21:23 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "libft.h"

# define VALUE_Y 18
# define TOTAL_SPECS VALUE_Y
# define IS_X(a) (((unsigned)a | 32) - 97 == 23u)
# define IS_O(a) (((unsigned)a | 32) - 97 == 14u)
# define IS_D(a) (((unsigned)a | 32) - 97 == 3u)
# define IS_U(a) (((unsigned)a | 32) - 97 == 20u)
# define ISXO(a) ((IS_X(a)) || (IS_O(a)))
# define ISLENMOD(a) (a == 'h' || a == 'l' || a == 'j' || a == 'z')

typedef struct	s_vect
{
	size_t		size;
	size_t		init;
	char		*string;
}				t_vect;

typedef	struct	s_xou
{
	char		size;
	char		**string;
}				t_xou;

typedef enum	e_bool
{
	false,
	true
}				t_bool;

typedef struct	s_printf
{
	char		*ret;
	const char	*format;
	int			len;
}				t_printf;

typedef struct	s_vector
{
	size_t		len;
	size_t		cap;
	char		*data;
}				t_vector;

typedef struct	s_chr
{
	wchar_t		chr;
	char		*str;
	int			len;
	int			i;
	int			null;
}				t_chr;

typedef struct	s_fmt
{
	size_t		i;
	const char	*str;
	const char	string[6];
	int			res;
}				t_fmt;

typedef	struct	s_spec
{
	int			i;
	const char	**format;
	char		*str;
}				t_spec;

typedef struct	s_num
{
	char		l;
	intmax_t	val;
	uintmax_t	octal;
	uintmax_t	hex;
	uintmax_t	unsonian;
	char		*s;
}				t_num;

typedef	struct	s_bonus
{
	int			i;
	intmax_t	*d;
}				t_bonus;

typedef enum	e_lenmod
{
	hh,
	h,
	l,
	ll,
	j,
	z
}				t_lenmod;

typedef	struct	s_handl
{
	char		*new;
	char		extra;
	char		*orig;
	int			number;
	size_t		numb;
}				t_handl;

typedef enum	e_flag
{
	LFT = 1 << 0,
	POS = 1 << 1,
	INV = 1 << 2,
	ZER = 1 << 3,
	HTG = 1 << 4
}				t_flag;

typedef struct	s_info
{
	char		flags;
	char		length;
	char		spec;
	int			width;
	int			prec;
	int			pset:1;
}				t_info;

typedef	struct	s_str
{
	char		*tmp;
	char		*ctmp;
	char		*s;
}				t_str;

typedef struct	s_convtbl
{
	char spec;
	void (*f)(t_vector *, t_info *, va_list);
}				t_convtbl;

typedef	struct	s_wstr
{
	wchar_t		*duplicate;
	size_t		size;
	size_t		i_val;
	char		*value;
}				t_wstr;

/*
**  Main Functions
*/

int				ft_printf(const char *format, ...);
int				ft_sprintf(char *str, const char *format, ...);
int				ft_snprintf(char *str, size_t size, const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

/*
**  Main Support
*/

int				ft_vasprintf(char **ret, const char *format, va_list ap);
int				ft_strprintf(char **ret, const char *format, va_list ap);

/*
**	Dispatcher Functions
*/

void			ft_get_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_handle_spec(t_vector *vector, const char **format,
												t_info *pfinfo, va_list ap);

/*
**	Format Specifier Parse Functions
*/

t_bool			ft_chk_flags(const char **format, t_info *pfinfo);
t_bool			ft_chk_width(const char **format, t_info *pfinfo, va_list ap);
t_bool			ft_chk_prec(const char **format, t_info *pfinfo, va_list ap);
t_bool			ft_chk_len(const char **format, t_info *pfinfo);

/*
**	Vector Functions (Dyanamic Char Array)
*/

int				ft_vector_init(t_vector *vector, size_t init_cap);
void			ft_vector_append(t_vector *vector, char *newdata);
void			ft_vector_resize(t_vector *vector, size_t min);
void			ft_vector_nappend(t_vector *vector, char *newdata, size_t n);
void			ft_vector_free(t_vector *vector);

/*
**  Conversion Functions
*/

void			ft_num_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_str_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_wstr_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_pct_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_chr_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_octal_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_hex_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_uns_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_binary_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_float_conv(t_vector *vector, t_info *pfinfo, va_list ap);
void			ft_none_conv(t_vector *vector, t_info *pfinfo, va_list ap);

/*
**	Conversion Helpers
*/

void			ft_pad_handle(t_info *pfinfo, char **str);
void			ft_prec_handle(t_info *pfinfo, char **str);
void			ft_prec_nums(t_info *pfinfo, char **str);
int				ft_unicode_b(wchar_t chr);
void			ft_unicode_conv(wchar_t chr, char *str);
char			*ft_null_str(t_info *pfinfo);
uintmax_t		ft_xou_len(char length, va_list ap);
void			ft_handle_xou(char **str, t_info *pfinfo);

/*
**	Helpers
*/

void			ft_pfinfo_init(t_info *pfinfo);
t_bool			ft_pfcolors(t_vector *vector, const char **format);

#endif
