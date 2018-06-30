/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 11:04:03 by stestein          #+#    #+#             */
/*   Updated: 2018/06/29 17:36:35 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include "includes/libftprintf.h"
 
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
 
// These vars will contain the hash
uint32_t h0, h1, h2, h3;
 
void md5(uint8_t *initial_msg, size_t initial_len)
{
 
    uint8_t *msg;

	msg = NULL;	
    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
					};
    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
 
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
 
    int new_len;
	
	new_len = initial_len*8 + 1;
	while (new_len%512!=448)
		new_len++;
    new_len /= 8;
 
    msg = malloc(sizeof(int) * (new_len + 64)); // also appends "0" bits 
                                   // (we alloc also 64 extra bytes...)
    ft_memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit
 
    uint32_t bits_len = 8*initial_len; // note, we append the len
    ft_memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer
 
    // Process the message in successive 512-bit chunks:
    // for each 512-bit chunk of message:


    int offset;

	offset = 0;
	while (offset < new_len)
	{

        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);
 
        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
 
        // Main loop:
        uint32_t i = 0;
		while (i < 64)
		{
            uint32_t f, g;
 
             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;          
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;
			i++;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
 		offset += (512/8);
    }
    free(msg);
}

int		q_check(char **argv, int arg)
{
	int i = 0;

	while (argv[arg][i])
	{
		if (argv[arg][i] == 'q')
			return (1);
		i++;
	}
	return (0);
}

int		r_check(char **argv, int arg)
{
	int i = 0;

	while (argv[arg][i])
	{
		if (argv[arg][i] == 'r')
			return (1);
		i++;
	}
	return (0);
}

int		s_check(char **argv, int arg)
{
	int i = 0;

	while (argv[arg][i])
	{
		if (argv[arg][i] == 's')
			return (1);
		i++;
	}
	return (0);
}

void	print_usage(int type)
{
	if (type == 'p')
	{
		ft_printf("Invalid Flags. -p flag must be used alone\n");
		ft_printf("Try:	echo \"string\" | ./ft_ssl md5 -p\n");
	}
}

void	p_flag(char **argv, int v, int file_index)
{
	int status = 0;
	char tmp[2000];
	char *file_contents;
	int ret = 0;
	char buffer[1];
	char *msg;
	int i = 0;
	int fd = 0;

	if (!(argv[v][2] == '\0' || argv[v][2] == 0))
	{
			print_usage('p');
			exit (1);
	}
	while (status >= 0)
	{
		//stdin reading from fd = 0
		while ((ret = read(fd, buffer, 1)))
			tmp[i++] = buffer[0];
		if (close(fd) == -1)
			break;	
		tmp[--i] = '\0';
		file_contents = ft_strdup(tmp);
		msg = file_contents;
		status++;
	   	break;	// sets status to prevent argv[file_index] from running
				// which normally runs when no file could be opened 
	}
	if (status > 0)
		ft_printf("%s\n", msg);
	if (status == 0)	
	{
		ft_printf("%s\n", argv[file_index]);
		msg = argv[file_index];
	}
   	size_t len = ft_strlen(msg);
	md5(msg, len);
	uint8_t *p;	
	p=(uint8_t *)&h0;
    ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
 	p=(uint8_t *)&h1;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);
	p=(uint8_t *)&h2;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);
	p=(uint8_t *)&h3;
	ft_printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3], h3);
}

void	s_flag(char **argv, int v, int file_index)
{
	int qcheck = 0;
	int rcheck = 0;
	int scheck = 0;

	qcheck = q_check(argv, 2);
	rcheck = r_check(argv, 2);
	scheck = s_check(argv, 2);
	if (qcheck != 1 && rcheck != 1)
		ft_printf("MD5 (\"%s\") = ", argv[file_index]);
	char *msg = argv[file_index];
   	size_t len = ft_strlen(msg);
	md5(msg, len);
	uint8_t *p;
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
		ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);
	while (1)
	{
		if (rcheck == 1 && qcheck == 0)
		{
			if (scheck == 1)
			{
				ft_printf(" \"%s\"\n", argv[file_index]);
				break;
			}
			ft_printf(" %s\n", argv[file_index]);
		}
		break;
	}
}	

int main(int argc, char **argv)
{
	int v;
	int save;
	int file_index;
	size_t len;
	uint8_t *p;

	v = 1;
	file_index = 0;
    if (argc < 2)
	{
        ft_printf("usage: %s HASH_TYPE -FLAGS THING_TO_HASH\n", argv[0]);
        return (1);
    }
	if (ft_strcmp(argv[v], "md5") == 0)
	{
		file_index = ++v;
		// handles input of flags preceeded with -
		
		if ((argv[v] != 0 && argv[v][0] == '-') && 
				(argv[v][1] == 's' || argv[v][1] == 'q' == 0 ||
				argv[v][1] == 'r' == 0 || argv[v][1] == 'p'))
		{
			file_index++;
			if (argv[v][1] == 'p')
			{
				p_flag(argv, v, file_index);
				return (0);
			}
			if ((ft_strcmp(argv[v], "-s") == 0 || ft_strcmp(argv[v], "-qs") == 0
					|| ft_strcmp(argv[v], "-sq") == 0 || ft_strcmp(argv[v],
						"-qrs") == 0 || ft_strcmp(argv[v], "-rqs") == 0 ||
					ft_strcmp(argv[v], "-rs") == 0 || ft_strcmp(argv[v], "-sr") || 
					ft_strcmp(argv[v], "-srq") == 0 || ft_strcmp(argv[v], "-q") == 0) 
					&& argv[++v] != 0)
			{
				s_flag(argv, v, file_index);
				return (0);
			}
		}
		
		// if no flags, this will happen
		// first checks for possible file name passed as param
		// if no file with that name, check if a string was passed instead of a flag
		// (which is technically undefined behavior, but we're better than that)
		// if not a string, default to reading from stdin 
		
		int status = 0;
		int	fd = 0;
		
		if ((fd = open(argv[file_index], O_RDONLY)) == -1)
			status = -1; 
		if (status == -1 && argv[file_index] != 0)
		{		
			if (argv[file_index][0] >= 8 && argv[file_index][0] <= 126)
			{
				if (argv[file_index] <= 32)
				{
					ft_printf("%s\n", "Use printable characters or standard string notation");
					ft_printf("%s\n", "You should also probably use a -s flag for a string. derp.");
					return (0);
				}
				s_flag(argv, v, file_index);
				ft_printf("%s\n", "I hashed this as a courtesy, next time I won't be so nice. Use a flag or learn the md5 format pal.");
				return (0);
			}
		}

		int		ret = 0;
		char	buffer[1];
		char	tmp[2000];
		int		i = 0;
		char	*file_contents;
		char	*msg;
		int		rcheck = 0;
		int		qcheck = 0;
		int		ind = 3;

		while (status == -1)
		{
		// loop for stdin to read from fd = 0
		// and set msg to the stdin
			fd = 0;					// 	by breaking from this loop and hashing it, baby.
			while ((ret = read(fd, buffer, 1))) //this will indefinitely wait for input
				tmp[i++] = buffer[0];			// from stdin so we dont want to if there
			if (tmp == NULL)					// is another choice (like a string being
				break ;							// entered after ./a.out md5
			if (close(fd) == -1)
				break ;
			tmp[--i] = '\0';
			file_contents = ft_strdup(tmp);
			msg = file_contents;
	   		break;
		}
		if (status == 0)
		{
			if (argv[file_index][0] != '-')
				ind = 2;
			rcheck = r_check(argv, ind);
			qcheck = q_check(argv, ind);
		}
		if (status == 0)
		{
			while ((ret = read(fd, buffer, 1)))
				tmp[i++] = buffer[0];
			if (close(fd) == -1)
				return (-1);
			tmp[--i] = '\0';
			file_contents = ft_strdup(tmp);
			msg = file_contents;
			while (1)
			{
				if (qcheck == 1 || rcheck == 1)
					break;
		   		ft_printf("MD5 (%s) = ", argv[file_index]);
				break ;
			}
		}
	 	size_t len = ft_strlen(msg);
		md5(msg, len);
		uint8_t *p;
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
			ft_printf(" %s\n", argv[file_index]);
		}
		return (0);	
	}
}
