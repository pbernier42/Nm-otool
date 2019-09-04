/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:23:04 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/29 16:23:05 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <stdio.h>

# include "match_o.h"
# include "error_otool.h"
# include "utils.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/mman.h>


# define RETURN_SUCESS	0
# define RETURN_FAIL	-1

# define SIZE_BUFF			16
# define ERROR			0

// # define ALIGN(value)	(value + (!(value % 16) ? 0 : (16 - (value % 16))))

/*
**	ft_otool.c
*/

# define NUMBER_FLAGS	1
# define CHAR_FLAGS		"t"
# define LEN_FLAGS		len[0]
# define LEN_ARGV		len[1]
# define SIZE_ARGV		len[2]

typedef struct s_flags		t_flags;

struct						s_flags
{
	bool			text_section;
};

int		check_usage(int argc, char **argv, t_flags *flags);
int		check_flags(char *argv, char *flags);

/*
**	read_otool.c
*/

int		open_file(char *file);
int		read_file(void *data, unsigned long long size_file);

/*
**	print_otool.c
*/

# define MOD(hex)		(hex % 16)
# define HEXA_CHAR(hex)	(MOD(hex) > 9 ? MOD(hex) + 'a' - 10 : MOD(hex) + '0');

void		print_count(long long count);
void		print_data(unsigned char data[SIZE_BUFF], int read);

#endif
