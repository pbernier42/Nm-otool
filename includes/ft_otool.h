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

/*
**	main_otool.c
*/

typedef struct s_flags		t_flags;

# define NUMBER_FLAGS	3
# define CHAR_FLAGS		"tln"
# define RESET_FLAGS	((t_flags){0, 0, 0})
# define DONE_FLAGS		((bool*)&done)

struct						s_flags
{
	bool			text_section;
	bool			load_command;
	bool			symbols_file;
};


# define LEN_FLAGS		len[0]
# define LEN_ARGV		len[1]
# define SIZE_ARGV		len[2]

int			check_usage(int argc, char **argv, t_flags *flags, e_fonction fonction);
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
	e_symbols_file,
	e_no_flags
};

int			open_file(char *file, t_flags *flags);
int			type_file(char *file, void *data, t_flags *flags);
t_eflags	what_flag(char *flags);

/*
**	read_otool.c
*/

typedef struct s_match		t_match;

# define TEXT_SECT			"__text"
# define TEXT_SEG			"__TEXT"

# define M_SIZEOF_SEGM		match.tab[0]
# define M_SIZEOF_SECT		match.tab[1]
# define M_ADDR_NSECTS_SEGM	match.tab[2]
# define M_ADDR_SIZE		match.tab[3]

struct						s_match
{
	void		*header;
	uint32_t	lc_segment;
	uint32_t	ncmds;
	t_mh_comm	*command;
	void		*section;
	bool		endian;
	bool		__pad1[3];
	short		tab[4];
	t_eflags	flag;
};

int			read_match_32(void *data, bool endian, t_eflags flag);
int			read_match_64(void *data, bool endian, t_eflags flag);

int			read_match_text(void *data, t_ull address, t_ull size_file, short size);
int			read_match_nlist(t_match match, void **tab_nlist);
int			read_match_ntype(t_match match, void *nlist, char *type);

/*
**	f_fat_otool.c
*/

int		read_fat(void *data, bool endian, t_eflags flag);

/*
**	f_match_otool.c
*/

# define LC_SEGMENT 		0x1
# define LC_SYMTAB			0x2
# define LC_SEGMENT_64		0x19

# define FLAG				(match.flag)
# define COMMAND			((void *)match.command)
# define SEGMENT_NSECTS		*((uint32_t*)(COMMAND + M_ADDR_NSECTS_SEGM))
# define SECTION			(match.section)
# define SECTION_SECTNAME	((char*)SECTION)
# define SECTION_SEGNAME	((char*)(SECTION + 16))
# define SECTION_32			((t_mh_sect_32*)SECTION)
# define SECTION_64			((t_mh_sect_64*)SECTION)

# define SYMTAB				((t_st_comm*)match.command)

# define NLIST				(match.section)

# define LEN_TAB			len[0]
# define LEN_STRING			len[1]
# define LEN_SAVE			len[2]

# define N_STRX(adress)		(((t_st_nlis_64*)adress)->n_strx)
# define N_SECT(adress)		(((t_st_nlis_64*)adress)->n_sect)
# define N_VALUE(adress)	(((t_st_nlis_64*)adress)->n_value)
# define N_TYPE(adress)		(((t_st_nlis_64*)adress)->n_type)
# define N_DESC(adress)		(((t_st_nlis_64*)adress)->n_desc)

//a revoir
# define SECTNAME(adress)	(&(((char*)(match.header + 103))[N_SECT(adress)]))
# define SYMTAB_STRING		((char*)(match.header + SYMTAB->symoff + SYMTAB->strsize))
# define STRING(adress)		(&(SYMTAB_STRING[N_STRX(adress)]))

int			read_match_file(t_match match);
int			read_match_symtab(t_match match);
int			sort_match_nlist(t_match match, void **tab_nlist);
char		what_sectname(char text[16]);
int			read_match_command(t_match match);
int			read_match_section(t_match match);

/*
**	fat_otool.c
*/

int		read_fat(void *data, bool endian, t_eflags flag);

/*
**	print_otool.c
*/

# define CHAR_SPACE		"                "

void 	print_header(void *data);
void 	print_command(void *data);
void	print_section(void *data);
void	print_data(unsigned char data[16], short size);



#endif
