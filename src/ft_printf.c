/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:52:02 by stestein          #+#    #+#             */
/*   Updated: 2018/06/06 12:30:26 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#define VAS t_printf *head; const char *retrn; head = NULL;
#define SNP va_list ap; t_printf *head; int retrn; head = NULL;

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	*head;
	int			save;

	save = 0;
	head = malloc(sizeof(t_printf));
	if ((!format || !*format) && save == 0)
	{
		free(head);
		return (0);
	}
	va_start(ap, format);
	save++;
	head->len = ft_vasprintf(&head->ret, format, ap);
	write(1, head->ret, head->len);
	free(head->ret);
	va_end(ap);
	save = head->len;
	free(head);
	return (save);
}

int		ft_vasprintf(char **ret, const char *format, va_list ap)
{
	VAS;
	head = malloc(sizeof(t_printf));
	head->format = format;
	if (*head->format == '\0')
		*ret = ft_strnew(0);
	if (!ret || !head->format || !*head->format)
	{
		free(head);
		return (0);
	}
	if (ft_strchr(head->format, '%') == NULL)
	{
		if ((*ret = ft_strdup(head->format)) == NULL)
		{
			free(head);
			return (-1);
		}
		free(head);
		return (ft_strlen(*ret));
	}
	retrn = head->format;
	free(head);
	return (ft_strprintf(ret, retrn, ap));
}

int		ft_sprintf(char *str, const char *format, ...)
{
	va_list		ap;
	t_printf	*head;
	int			retrn;

	head = NULL;
	if (!str || !format)
	{
		free(head);
		return (0);
	}
	va_start(ap, format);
	head->len = ft_vasprintf(&head->ret, format, ap);
	ft_strcpy(str, head->ret);
	free(head->ret);
	va_end(ap);
	retrn = head->len;
	free(head);
	return (retrn);
}

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	SNP;
	head = malloc(sizeof(t_printf));
	if (!str || !format)
	{
		free(head);
		return (0);
	}
	va_start(ap, format);
	head->len = ft_vasprintf(&head->ret, format, ap);
	if (size == 0)
	{
		free(head);
		return (head->len);
	}
	else if (size - 1 == 0)
		str[0] = '\0';
	ft_strncpy(str, head->ret, size - 1);
	free(head->ret);
	va_end(ap);
	retrn = head->len;
	free(head);
	return (retrn);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list		ap;
	t_printf	*head;
	int			retrn;

	head = NULL;
	head = malloc(sizeof(t_printf));
	if (!format || !*format || fd < 0)
	{
		free(head);
		return (0);
	}
	va_start(ap, format);
	head->len = ft_vasprintf(&head->ret, format, ap);
	write(fd, head->ret, head->len);
	free(head->ret);
	va_end(ap);
	retrn = head->len;
	free(head);
	return (retrn);
}
