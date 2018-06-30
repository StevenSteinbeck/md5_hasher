/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfbonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:32:05 by stestein          #+#    #+#             */
/*   Updated: 2018/06/06 12:18:24 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#define FLAG_HH return ((intmax_t *)va_arg(ap, signed char *));
#define FLAG_H return ((intmax_t *)va_arg(ap, short *));
#define FLAG_L return ((intmax_t *)va_arg(ap, long *));
#define FLAG_LL return ((intmax_t *)va_arg(ap, long long *));
#define FLAG_J return ((intmax_t *)va_arg(ap, intmax_t *));
#define FLAG_Z return ((intmax_t *)va_arg(ap, ssize_t *));

char g_colors[33][2][15] = {
	{"{byellow}", "\033[33;1m"},
	{"{cyan}", "\033[36m"},
	{"{green}", "\033[32m"},
	{"{yellow}", "\033[33m"},
	{"{purple}", "\033[35m"},
	{"{bblue}", "\033[34;1m"},
	{"{bcyan}", "\033[36;1m"},
	{"{red}", "\033[31m"},
	{"{bred}", "\033[31;1m"},
	{"{black}", "\033[30m"},
	{"{bgreen}", "\033[32;1m"},
	{"{bwhite}", "\033[37;1m"},
	{"{white}", "\033[37m"},
	{"{b_bgreen}", "\033[42;1m"},
	{"{b_byellow}", "\033[43;1m"},
	{"{bblack}", "\033[30;1m"},
	{"{b_bred}", "\033[41;1m"},
	{"{b_red}", "\033[41m"},
	{"{blue}", "\033[34m"},
	{"{b_bcyan}", "\033[46;1m"},
	{"{b_yellow}", "\033[43m"},
	{"{b_bpurple}", "\033[45;1m"},
	{"{b_bblue}", "\033[44;1m"},
	{"{b_black}", "\033[40m"},
	{"{b_green}", "\033[42m"},
	{"{b_blue}", "\033[44m"},
	{"{b_white}", "\033[47m"},
	{"{b_bblack}", "\033[40;1m"},
	{"{b_cyan}", "\033[46m"},
	{"{b_bwhite}", "\033[47;1m"},
	{"{eoc}", "\033[0m"},
	{"{b_purple}", "\033[45m"}
};

t_bool		ft_pfcolors(t_vector *vector, const char **format)
{
	t_bonus head;
	t_bonus	*top;

	top = malloc(sizeof(t_bonus));
	while (head.i < 33)
	{
		top->i = head.i;
		if (ft_strnstr(*format, g_colors[head.i][0], \
					ft_strlen(g_colors[head.i][0])) != 0)
		{
			top->i++;
			ft_vector_append(vector, g_colors[head.i][1]);
			*format = *format + ft_strlen(g_colors[head.i][0]);
			free(top);
			return (true);
		}
		++head.i;
	}
	free(top);
	return (false);
}

void		ft_binary_conv(t_vector *vector, t_info *pfinfo, va_list ap)
{
	t_num	head;
	t_num	*top;

	top = malloc(sizeof(t_num));
	head.hex = va_arg(ap, unsigned long long);
	head.s = ft_uimaxtoa_base(head.hex, 2, "01");
	top->s = head.s;
	ft_handle_xou(&head.s, pfinfo);
	ft_vector_append(vector, head.s);
	free(head.s);
	free(top);
}

intmax_t	*ft_printf_n_len(t_info *pfinfo, va_list ap)
{
	int i;

	i = 0;
	if (pfinfo->length == hh && i < 33)
		FLAG_HH;
	i++;
	if (pfinfo->length == h && i < 33)
		FLAG_H;
	if (pfinfo->length == l && i < 33)
		FLAG_L;
	if (pfinfo->length == ll && i < 33)
		FLAG_LL;
	i++;
	if (pfinfo->length == j && i < 33)
		FLAG_J;
	if (pfinfo->length == z && i < 33)
		FLAG_Z;
	return ((intmax_t *)va_arg(ap, int *));
}

void		ft_none_conv(t_vector *vector, t_info *pfinfo, va_list ap)
{
	t_bonus	head;
	t_bonus	*top;

	top = malloc(sizeof(t_bonus));
	head.i = vector->len;
	top->i = head.i;
	head.d = ft_printf_n_len(pfinfo, ap);
	*head.d = (intmax_t)head.i;
	free(top);
}
