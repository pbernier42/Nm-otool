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

# include <struct.h>
# include <error.h>
# include <utils.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>

# include <stdbool.h>

/*
**	main_otool.c
*/

typedef struct s_flags		t_flags;

# define NUMBER_FLAGS	2
# define CHAR_FLAGS		"tl"
# define RESET_FLAGS	((t_flags){0, 0})
# define DONE_FLAGS		((bool*)&done)

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

# define NUM_TYPE		5
# define ALL_MAGIC		MH_MAGIC, MH_MAGIC_64, FAT_MAGIC, FAT_MAGIC_64, ARC_MAGIC
# define ALL_CIGAM		MH_CIGAM, MH_CIGAM_64, FAT_CIGAM, FAT_CIGAM_64, ARC_CIGAM
# define TAB_MAGIC		((uint32_t[NUM_TYPE * 2]){ALL_MAGIC, ALL_CIGAM})
# define ALL_FT			read_match_32, read_match_64, read_fat, NULL, NULL
# define TAB_FT			((int ((*[NUM_TYPE])(void *, bool, t_eflags))){ALL_FT})

typedef enum e_flags	t_eflags;

enum					e_flags
{
	e_text_section,
	e_load_command,
	e_no_flags
};

int			open_file(char *file, t_flags *flags);
int			type_file(char *file, void *data, t_flags *flags);
t_eflags	what_flag(char *flags);

/*
**	read_otool.c
*/

# define TEXT_SECT			"__text"
# define TEXT_SEG			"__TEXT"

int			read_match_32(void *data, bool endian, t_eflags flag);
int			read_match_64(void *data, bool endian, t_eflags flag);

int			read_text(void *data, t_ull address, t_ull size_file, short size);
bool		same_text(char text[16], char check[16]);


/*
**	f_fat_otool.c
*/

int		read_fat(void *data, bool endian, t_eflags flag)

/*
**	match_otool.c
*/

typedef struct s_match		t_match;

# define M_SIZEOF_SEGM		match.tab[0]
# define M_SIZEOF_SECT		match.tab[1]
# define M_ADDR_NSECTS_SEGM	match.tab[2]

struct						s_match
{
	void		*header;
	uint32_t	lc_segment;
	uint32_t	ncmds;
	t_mh_comm	*command;
	void		*section;
	bool		endian;
	char		__pad1[1];
	short		tab[3];
	t_eflags	flag;
	char		__pad2[4];
};

# define LC_SEGMENT 		0x1
# define LC_SEGMENT_64		0x19


# define COMMAND			((void *)match.command)
# define SEGMENT_NSECTS		*((uint32_t*)(COMMAND + M_ADDR_NSECTS_SEGM))
# define SECTION			match.section
# define SECTION_SECTNAME	((char*)SECTION)
# define SECTION_SEGNAME	((char*)(SECTION + 16))
# define SECTION_32			((t_mh_sect_32*)SECTION)
# define SECTION_64			((t_mh_sect_64*)SECTION)


int			read_match_file(t_match match);
int			read_match_command(t_match match);
int			read_match_section(t_match match);

/*
**	fat_otool.c
*/

int		read_fat(void *data, bool endian, t_eflags flag);

/*
**	print_otool.c
*/

# define CHAR_SPACE		"            "

void 	print_header(void *data);
void 	print_command(void *data);
void	print_section(void *data);
void	print_data(unsigned char data[16], short size);



#endif
