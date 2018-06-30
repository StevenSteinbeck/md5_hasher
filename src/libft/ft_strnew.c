/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:56:56 by stestein          #+#    #+#             */
/*   Updated: 2018/06/06 13:13:57 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define STRNEW char *str; char *start;

char	*ft_strnew(size_t size)
{
	t_libft	*head;

	STRNEW;
	head = malloc(sizeof(t_libft));
	head->ret = "";
	free(head);
	if ((str = (char *)malloc(sizeof(char) * size + 1)) == 0)
		return (0);
	start = str;
	while (size--)
		*str++ = '\0';
	*str = '\0';
	return (start);
}
