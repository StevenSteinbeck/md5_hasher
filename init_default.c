/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 11:55:23 by stestein          #+#    #+#             */
/*   Updated: 2018/07/05 17:12:19 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

int		file_check(char **argv, int v, int *file_index, int *fd)
{
	int status = 99;
		
	if ((*fd = open(argv[*file_index], O_RDONLY)) == -1)
		status = -1; 
	if (status == -1 && argv[*file_index] != 0)
	{		
		if (argv[*file_index][0] >= 8 && argv[*file_index][0] <= 126)
		{
			if (argv[*file_index][0] <= 32)
			{
				ft_printf("%s\n", "Use printable characters");
				ft_printf("%s\n", "Also, use the -s flag for a string");
				return (0);
			}
			s_flag(argv, v, *file_index);
			ft_printf("%s\n", "Use a flag, you know you're supposed to");
			return (0);
		}
	}
	return (status);
}

char		*read_stdin(char **argv, int v, int *file_index)
{
		int		ret = 0;
		char	buffer[1];
		char	tmp[1000];
		int		i = 0;
		char	*file_contents;
		char	*msg;
		int		fd = 0;
		int		status = 0;

		while (status >= 0)
		{
			while ((ret = read(fd, buffer, 1)))
				tmp[i++] = buffer[0];
			if (close(fd) == -1)
				break ;
			tmp[--i] = '\0';
			file_contents = ft_strdup(tmp);
			msg = file_contents;
			status++;
			break ;
		}
		
		return (msg);
}

char	*file_hash(char **argv, int v, int *file_index, int *fd)
{
	int ind = 2;
	int rcheck = 0;
	int qcheck = 0;
	int ret = 0;
	char buffer[1];
	char tmp[2000];
	int i = 0;
	char *file_contents;
	char *msg;

	if (argv[3] != 0)
	{
		rcheck = r_check(argv, ind);
		qcheck = q_check(argv, ind);
	}
	while ((ret = read(*fd, buffer, 1)))
		tmp[i++] = buffer[0];
	if (close(*fd) == -1)
		return (NULL);
	tmp[--i] = '\0';
	file_contents = ft_strdup(tmp);
	msg = file_contents;
	while (1)
	{
		if (qcheck == 1 || rcheck == 1)
			break ;
   		ft_printf("MD5 (%s) = ", argv[*file_index]);
		break ;
	}
	return (msg);
}

void	print_msg(char *msg, int ind, char **argv, int *file_index)
{
	size_t	len;
	uint8_t	*p;
	int rcheck = 0;
	int qcheck = 0;
	
	if (argv[3] != 0)
	{
		rcheck = r_check(argv, ind);
		qcheck = q_check(argv, ind);
	}
	len = ft_strlen(msg);
	md5(msg, len);
	p=(uint8_t *)&h0;
    ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
 	p=(uint8_t *)&h1;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);
	p=(uint8_t *)&h2;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);
	p=(uint8_t *)&h3;
	if (rcheck == 0 || qcheck == 1)
		ft_printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3], h3);
	if (rcheck == 1 && qcheck == 0)
	{
		ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);
		ft_printf(" %s\n", argv[*file_index]);
	}
}

void	print_ncheck_msg(char *msg, char **argv, int *file_index)
{
	size_t	len;
	uint8_t	*p;

	len = ft_strlen(msg);
	md5(msg, len);
	p=(uint8_t *)&h0;
    ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
 	p=(uint8_t *)&h1;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);
	p=(uint8_t *)&h2;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);
	p=(uint8_t *)&h3;
	ft_printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3], h3);
}


int		init_default(char **argv, int v, int *file_index)
{
	int status;
	char *msg;
	int fd;
	int ind;
	int rcheck = 0;
	int qcheck = 0;
	int skip_checks = 0;
	
	ind = 2;
	status = 0;
	fd = 0;
	status = file_check(argv, v, file_index, &fd);
	while (1)
	{
		if (status == 0)
			return (0);
		if (status == -1)
		{
			msg = read_stdin(argv, v, file_index);
			skip_checks++;
			break ;
		}
		if (status == 99)
		{
			msg = file_hash(argv, v, file_index, &fd);
			break ;
		}
		break ;
	}
	if (skip_checks == 0)
		print_msg(msg, ind, argv, file_index);
	if (skip_checks == 1)
		print_ncheck_msg(msg, argv, file_index);
	return (0);
}

