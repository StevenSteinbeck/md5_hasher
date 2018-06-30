/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xou_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 19:26:48 by stestein          #+#    #+#             */
/*   Updated: 2018/06/06 12:59:54 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#define FLAG_HH return ((unsigned char)va_arg(ap, int));
#define FLAG_H return ((unsigned short)va_arg(ap, int));
#define FLAG_L return (va_arg(ap, unsigned long));
#define FLAG_LL return (va_arg(ap, unsigned long long));
#define FLAG_J return (va_arg(ap, uintmax_t));
#define FLAG_Z return (va_arg(ap, size_t));

uintmax_t	ft_xou_len(char length, va_list ap)
{
	if (length == hh)
		FLAG_HH;
	if (length == h)
		FLAG_H;
	if (length == l)
		FLAG_L;
	if (length == ll)
		FLAG_LL;
	if (length == j)
		FLAG_J;
	if (length == z)
		FLAG_Z;
	return (va_arg(ap, unsigned int));
}

void		ft_handle_alt(t_info *pfinfo, char **str)
{
	t_printf	head;
	t_printf	*top;

	if (!(ISXO(pfinfo->spec) || pfinfo->spec == 'p' || pfinfo->spec == 'b'))
		return ;
	top = malloc(sizeof(t_printf));
	head.ret = ft_strdup(*str);
	if (pfinfo->spec == 'p')
		ft_insrt_to_str(&head.ret, "0x");
	else if (pfinfo->flags & HTG)
	{
		if (pfinfo->spec == 'b' && ft_strcmp("0", *str) &&
														ft_strcmp("\0", *str))
			ft_insrt_to_str(&head.ret, "0b");
		else if (IS_X(pfinfo->spec) && ft_strcmp("0", *str) &&
														ft_strcmp("\0", *str))
			ft_insrt_to_str(&head.ret, "0x");
		else if (IS_O(pfinfo->spec) && **str != '0')
			ft_insrt_to_str(&head.ret, "0");
	}
	free(*str);
	free(top);
	*str = head.ret;
}

void		ft_x_toupper(char *str, char spec)
{
	t_xou	head;
	t_xou	*top;

	top = malloc(sizeof(t_xou));
	head.size = spec;
	if (head.size != 'X')
	{
		free(top);
		return ;
	}
	while (*str)
	{
		if (ISALPHA(*str))
			*str = TOUPPER(*str);
		str++;
	}
	free(top);
}

void		ft_handle_xou(char **str, t_info *pfinfo)
{
	t_xou	head;

	head.string = str;
	if (pfinfo->flags & ZER && pfinfo->prec == 0)
		pfinfo->flags ^= ZER;
	if (pfinfo->prec == 0 && !ft_strcmp(*head.string, "0"))
		**head.string = '\0';
	ft_prec_nums(pfinfo, head.string);
	if (pfinfo->flags & ZER && pfinfo->spec == 'p')
	{
		pfinfo->width = MAX(pfinfo->width - 2, 0);
		ft_pad_handle(pfinfo, head.string);
	}
	else if (pfinfo->flags & ZER && pfinfo->flags & HTG && (IS_X(pfinfo->spec)
														|| pfinfo->spec == 'b'))
	{
		pfinfo->width = MAX(pfinfo->width - 2, 0);
		ft_pad_handle(pfinfo, head.string);
	}
	ft_handle_alt(pfinfo, head.string);
	if (!(pfinfo->flags & ZER && pfinfo->flags & HTG && (IS_X(pfinfo->spec)
								|| pfinfo->spec == 'p' || pfinfo->spec == 'b')))
		ft_pad_handle(pfinfo, head.string);
	ft_x_toupper(*head.string, pfinfo->spec);
}
