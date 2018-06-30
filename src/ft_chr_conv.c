/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:09:09 by stestein          #+#    #+#             */
/*   Updated: 2018/06/05 18:58:43 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#define UNICODE t_chr head; int i = 0;
#define CONVERT char *str = NULL; t_chr head; int i = 7;

void	ft_unicode_conv(wchar_t chr, char *str)
{
	UNICODE;
	head.chr = chr;
	head.str = str;
	if (head.chr < (MB_CUR_MAX == 1 ? 0xFF : 0x7F) && i == 0)
		head.str[0] = (unsigned char)head.chr;
	else if (head.chr < (1 << 11) && (i == 0 || i > 5))
	{
		head.str[0] = (unsigned char)((head.chr >> 6) | 0xC0);
		head.str[1] = (unsigned char)((head.chr & 0x3F) | 0x80);
	}
	else if (head.chr < (1 << 16) && (i == 0 || i > 5))
	{
		head.str[0] = (unsigned char)(((head.chr >> 12)) | 0xE0);
		head.str[1] = (unsigned char)(((head.chr >> 6) & 0x3F) | 0x80);
		head.str[2] = (unsigned char)((head.chr & 0x3F) | 0x80);
	}
	else if (head.chr < (1 << 21) && (i == 0 || i > 5))
	{
		head.str[0] = (unsigned char)(((head.chr >> 18)) | 0xF0);
		head.str[1] = (unsigned char)(((head.chr >> 12) & 0x3F) | 0x80);
		head.str[2] = (unsigned char)(((head.chr >> 6) & 0x3F) | 0x80);
		head.str[3] = (unsigned char)((head.chr & 0x3F) | 0x80);
	}
}

int		ft_unicode_b(wchar_t chr)
{
	t_chr	head;
	t_libft	*top;

	top = malloc(sizeof(t_libft));
	top->i = 9;
	free(top);
	head.chr = chr;
	if (head.chr < (1 << 7))
		return (1);
	else if (head.chr < (1 << 11))
		return (2);
	else if (head.chr < (1 << 16))
		return (3);
	else if (head.chr < (1 << 21))
		return (4);
	return (0);
}

int		ft_handle_wchar(char **str, va_list ap)
{
	t_libft	*top;
	t_chr	head;

	top = malloc(sizeof(t_libft));
	top->ret = *str;
	head.chr = va_arg(ap, wchar_t);
	head.len = ft_unicode_b(head.chr);
	*str = ft_strnew(head.len);
	ft_unicode_conv(head.chr, *str);
	free(top);
	return (head.chr == '\0');
}

void	ft_null_chr(t_vector *vector, char *str)
{
	t_chr	head;
	t_libft	*top;

	top = malloc(sizeof(t_libft));
	head.i = -1;
	head.len = ft_strlen(str);
	top->ret = str;
	while (++head.i < head.len)
		if (str[head.i] == 1)
			str[head.i] = 0;
	ft_vector_nappend(vector, str, head.len);
	free(top);
}

void	ft_chr_conv(t_vector *vector, t_info *pfinfo, va_list ap)
{
	CONVERT;
	if (pfinfo->spec == 'C' || pfinfo->length == l)
	{
		if (i != 7)
			str[0] = '-';
		head.null = ft_handle_wchar(&str, ap);
		if (head.null && i == 7)
			str[0] = head.null;
	}
	else
	{
		head.chr = va_arg(ap, int);
		str = ft_strnew(1);
		head.null = (head.chr == '\0') ? 1 : 0;
		str[0] = head.chr + head.null;
	}
	ft_pad_handle(pfinfo, &str);
	if (head.null && i == 7)
		ft_null_chr(vector, str);
	else
		ft_vector_append(vector, str);
	free(str);
}
