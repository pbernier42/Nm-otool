/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:23:04 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/29 16:23:05 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# include <stdio.h>

# include <match_o.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>


# define BUFF			16
# define ERROR			0
# define MH_MAGIC_64	0xfeedfacf

# define ALIGN(value)	(value + (!(value % 16) ? 0 : (16 - (value % 16))))

/*
**	ft_otool.c
*/

bool		check_usage(int argc, char **argv);

/*
**	read_otool.c
*/

# define SIZE_HEADER	ALIGN(sizeof(t_header))
# define SIZE_SEGMENT	ALIGN(sizeof(t_segment))

bool		read_file(char *file);
void		read_header(int fd);
void		read_data(int fd);

/*
**	print_otool.c
*/

# define MOD(hex)		(hex % 16)
# define HEXA_CHAR(hex)	(MOD(hex) > 9 ? MOD(hex) + 'a' - 10 : MOD(hex) + '0');

bool		print_usage(void);
void		print_count(long long count);
void		print_data(unsigned char data[BUFF], int read);

#endif
