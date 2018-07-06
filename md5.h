/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stestein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 11:55:50 by stestein          #+#    #+#             */
/*   Updated: 2018/06/30 14:00:24 by stestein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
#define MD5_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include "includes/libftprintf.h"
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

uint32_t h0, h1, h2, h3;

int		file_check(char **argv, int v, int *file_index, int *fd);
char	*read_stdin(char **argv, int v, int *file_index);
char	*file_hash(char **argv, int v, int *file_index, int *fd);
void	print_msg(char *msg, int ind, char **argv, int *file_index);
int		init_default(char **argv, int v, int *file_index);
void 	md5(uint8_t *initial_msg, size_t initial_len);
int		q_check(char **argv, int arg);
int		r_check(char **argv, int arg);
int		s_check(char **argv, int arg);
void	print_usage(int type);
void	p_flag(char **argv, int v, int file_index);
void	s_flag(char **argv, int v, int file_index);

#endif
