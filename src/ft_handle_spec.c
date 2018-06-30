/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:58:12 by stestein          #+#    #+#             */
/*   Updated: 2018/06/06 12:02:20 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#define HANDLE t_spec head; head.format = format; int i = 0;
#define HANDLEE pfinfo->width = 0; pfinfo->prec = -1; pfinfo->spec = 'N';
#define HANDLEEE pfinfo->flags = 0; pfinfo->length = -1; pfinfo->pset = 0;

t_convtbl g_convtbl[] =
{
	{'d', &ft_num_conv},
	{'D', &ft_num_conv},
	{'i', &ft_num_conv},
	{'p', &ft_hex_conv},
	{'o', &ft_octal_conv},
	{'O', &ft_octal_conv},
	{'x', &ft_hex_conv},
	{'X', &ft_hex_conv},
	{'u', &ft_uns_conv},
	{'U', &ft_uns_conv},
	{'s', &ft_str_conv},
	{'S', &ft_wstr_conv},
	{'c', &ft_chr_conv},
	{'C', &ft_chr_conv},
	{'b', &ft_binary_conv},
	{'f', &ft_float_conv},
	{'n', &ft_none_conv},
	{'%', &ft_pct_conv}
};

void	ft_get_conv(t_vector *vector, t_info *pfinfo, va_list ap)
{
	t_spec head;
	t_spec *top;

	top = malloc(sizeof(t_spec));
	head.i = -1;
	while (++head.i < TOTAL_SPECS)
	{
		top->i = head.i;
		if (pfinfo->spec == g_convtbl[head.i].spec)
		{
			g_convtbl[head.i].f(vector, pfinfo, ap);
			free(top);
			return ;
		}
	}
	top->i = head.i;
	free(top);
	ft_pct_conv(vector, pfinfo, ap);
}

void	ft_handle_spec(t_vector *vector, const char **format,
													t_info *pfinfo, va_list ap)
{
	HANDLE;
	if (**head.format == '{' && i < 90)
		if (ft_pfcolors(vector, head.format) == true)
			return ;
	while (1)
	{
		i++;
		if (ft_chk_flags(head.format, pfinfo))
			continue ;
		if (ft_chk_width(head.format, pfinfo, ap))
			continue ;
		if (ft_chk_prec(head.format, pfinfo, ap))
			continue ;
		if (ft_chk_len(head.format, pfinfo))
			continue ;
		if (**head.format == '\0')
			return ;
		pfinfo->spec = *(*head.format)++;
		break ;
	}
	ft_get_conv(vector, pfinfo, ap);
	i = i + 90;
}

int		ft_strprintf(char **ret, const char *format, va_list ap)
{
	t_spec		head;
	t_vector	vector;
	t_info		pfinfo;

	ft_pfinfo_init(&pfinfo);
	if (ft_vector_init(&vector, ft_strlen(format) + 50) == FAILED)
		return (FAILED);
	while (*format)
	{
		head.i = 0;
		while (format[head.i] && format[head.i] != '%')
			head.i++;
		ft_vector_nappend(&vector, (char *)format, head.i);
		format += head.i;
		if (*format == '%')
		{
			if (*(++format) == 0)
				break ;
			ft_handle_spec(&vector, &format, &pfinfo, ap);
		}
		ft_pfinfo_init(&pfinfo);
	}
	*ret = ft_strndup(vector.data, vector.len);
	ft_vector_free(&vector);
	return (vector.len);
}

void	ft_pfinfo_init(t_info *pfinfo)
{
	HANDLEE;
	HANDLEEE;
}

void	ft_pct_conv(t_vector *vector, t_info *pfinfo, va_list ap)
{
	t_spec head;
	t_spec *new;

	new = malloc(sizeof(t_spec));
	(void)ap;
	head.str = ft_strnew(1);
	new->str = head.str;
	*head.str = pfinfo->spec;
	ft_pad_handle(pfinfo, &head.str);
	ft_vector_append(vector, head.str);
	free(head.str);
	free(new);
}
