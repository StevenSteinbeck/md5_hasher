/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstr_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:51:24 by stestein          #+#    #+#             */
/*   Updated: 2018/06/06 13:01:10 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

wchar_t	*ft_wstrdup(wchar_t *str)
{
	t_wstr	head;
	t_wstr	*alloc;

	alloc = malloc(sizeof(t_wstr));
	head.size = 0;
	alloc->size = 0;
	while (str[head.size])
		++head.size;
	head.duplicate = (wchar_t *)malloc(sizeof(wchar_t) * (head.size + 1));
	free(alloc);
	if (!head.duplicate)
		return (NULL);
	head.size = 0;
	while (str[head.size])
	{
		head.duplicate[head.size] = str[head.size];
		head.size++;
	}
	head.duplicate[head.size] = '\0';
	return (head.duplicate);
}

size_t	ft_wstrlen(wchar_t *str)
{
	t_wstr	head;
	t_wstr	*top;

	top = malloc(sizeof(t_wstr));
	head.i_val = 0;
	head.size = 0;
	while (str[head.i_val])
	{
		top->size = ft_unicode_b(str[head.i_val]);
		head.size += ft_unicode_b(str[head.i_val]);
		head.i_val++;
	}
	free(top);
	return (head.size);
}

void	ft_prec_wstr(t_info *pfinfo, wchar_t *str)
{
	t_wstr	head;
	t_wstr	*top;

	top = malloc(sizeof(t_wstr));
	head.i_val = 0;
	head.size = 0;
	if (pfinfo->prec == -1)
	{
		free(top);
		return ;
	}
	if (ft_wstrlen(str) <= (size_t)pfinfo->prec)
	{
		free(top);
		return ;
	}
	while (str[head.i_val] && head.size <= (size_t)pfinfo->prec)
	{
		top->size = ft_unicode_b(str[head.i_val]);
		head.size += ft_unicode_b(str[head.i_val]);
		head.i_val++;
	}
	free(top);
	str[head.i_val - 1] = '\0';
}

char	*ft_wstr_to_str(wchar_t *wstr)
{
	t_wstr	head;
	t_wstr	*top;

	top = malloc(sizeof(t_wstr));
	head.i_val = 0;
	head.size = 0;
	head.value = ft_strnew(ft_wstrlen(wstr));
	while (wstr[head.i_val])
	{
		top->size = ft_unicode_b(wstr[head.i_val]);
		ft_unicode_conv(wstr[head.i_val], head.value + head.size);
		head.size += ft_unicode_b(wstr[head.i_val]);
		head.i_val++;
	}
	free(top);
	return (head.value);
}

void	ft_wstr_conv(t_vector *vector, t_info *pfinfo, va_list ap)
{
	t_wstr	head;
	t_wstr	*top;

	top = malloc(sizeof(t_wstr));
	head.duplicate = va_arg(ap, wchar_t *);
	if (!head.duplicate)
		head.value = ft_null_str(pfinfo);
	else
	{
		top->duplicate = ft_wstrdup(head.duplicate);
		head.duplicate = ft_wstrdup(head.duplicate);
		ft_prec_wstr(pfinfo, head.duplicate);
		head.value = ft_wstr_to_str(head.duplicate);
		free(top->duplicate);
		free(head.duplicate);
	}
	ft_pad_handle(pfinfo, &head.value);
	ft_vector_append(vector, head.value);
	free(head.value);
	free(top);
}
