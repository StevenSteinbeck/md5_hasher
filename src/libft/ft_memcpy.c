/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:56:43 by stestein          #+#    #+#             */
/*   Updated: 2018/06/03 13:56:45 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d_str;
	const unsigned char	*s_str;

	d_str = (unsigned char *)dst;
	s_str = (const unsigned char *)src;
	while (n--)
		*d_str++ = *s_str++;
	return (dst);
}
