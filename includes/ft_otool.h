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
# include <sys/mman.h>



/*
**	ft_otool.c
*/

typedef struct s_flags		t_flags;

# define NUMBER_FLAGS	2
# define CHAR_FLAGS		"tl"

struct						s_flags
{
	bool			text_section;
	bool			load_command;
};


# define LEN_FLAGS		len[0]
# define LEN_ARGV		len[1]
# define SIZE_ARGV		len[2]

int			check_usage(int argc, char **argv, t_flags *flags);
int			check_flags(char *argv, char *flags);

/*
**	open_otool.c
*/

# define ALL_MAGIC		MH_MAGIC, MH_MAGIC_64, FAT_MAGIC, FAT_MAGIC_64
# define ALL_CIGAM		MH_CIGAM, MH_CIGAM_64, FAT_CIGAM, FAT_CIGAM_64
# define TAB_MAGIC		((uint32_t[8]){ALL_MAGIC, ALL_CIGAM})
# define ALL_FT			NULL, read_match_64, read_fat_64, read_fat_64
# define TAB_FT			((int ((*[4])(void *, t_ull, bool, t_eflags))){ALL_FT})

typedef enum e_flags	t_eflags;

enum					e_flags
{
	e_text_section,
	e_load_command,
	e_no_flags
};

int			open_file(char *file, t_flags *flags);
int			type_file(char *file, void *data, t_ull size_file, t_flags *flags);
t_eflags	what_flag(char *flags);

/*
**	read_otool.c
*/

# define COUNT_COMMAND		count[0]
# define COUNT_SECTION		count[1]
# define SIZE_MH_HEAD_64	sizeof(t_mh_head_64)
# define SIZE_MH_SEGM_64	sizeof(t_mh_segm_64)
# define TEXT_SECT			"__text"
# define TEXT_SEG			"__TEXT"

int			read_match_64(void *data, t_ull size_file, bool endian,
	t_eflags flag);
int			read_fat_64(void *data, t_ull size_file, bool endian,
	t_eflags flag);

int			read_text(void *data, t_ull address, t_ull size);
bool		same_text(char text[16], char check[16]);

/*
**	print_otool.c
*/

# define CHAR_SPACE		"            "

# define LC_SEGMENT 	0x1
# define LC_SEGMENT_64	0x19

void 	print_header(void *data);
void 	print_command(void *data);
void	print_section(void *data);
void	print_data(unsigned char data[16], short size);

// void		print_count(t_ull count);
// void		print_data(unsigned char data[SIZE_BUFF], int read);

#endif
