/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:57:55 by stestein          #+#    #+#             */
/*   Updated: 2018/06/03 13:57:56 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char chr;
	unsigned char *str;

	chr = c & 0xff;
	str = (unsigned char *)b;
	while (len--)
		*str++ = chr;
	return (b);
}
