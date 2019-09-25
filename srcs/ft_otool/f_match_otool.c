/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_match_otool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:33:15 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/12 17:33:16 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>
#include <ft_nm.h>

//ATTENTO CORROMPU
//endian
int		read_match_file(t_match match)
{
	uint32_t		count_command;

	count_command = 0;
	while (count_command++ < match.ncmds)
	{
		if (FLAG == e_symbols_file
			&& match.command->cmd == LC_SYMTAB
			&& !read_match_symtab(match))
			return (RETURN_SUCESS);
		else if (FLAG == e_text_section
			&& match.command->cmd == match.lc_segment
			&& !read_match_command(match))
			return (RETURN_SUCESS);
		match.command = COMMAND + match.command->cmdsize;
	}
	//ajouter pas touver LC_SYMTAB
	return (error_otool(ERROR_FILE___TEXT));
}

int		read_match_symtab(t_match match)
{
	uint32_t		count_nlist;
	void*			tab_nlist[SYMTAB->nsyms];

	count_nlist = 0;
	NLIST = match.header + SYMTAB->symoff;
	while (count_nlist++ < SYMTAB->nsyms)
	{
		sort_match_nlist(SYMTAB_STRING, tab_nlist, NLIST, SYMTAB->nsyms);
		NLIST += sizeof(t_st_nlis_64);
	}
	if (read_match_nlist(match, tab_nlist))
	 	return (RETURN_FAIL);
	return (RETURN_SUCESS);
}

# define LEN_TAB			len[0]
# define LEN_STRING			len[1]
# define LEN_SAVE			len[2]

# define N_STRX(adress)		(((t_st_nlis_64*)adress)->n_strx)
# define STRING(adress)		(&(string[N_STRX(adress)]))


int	sort_match_nlist(char *string, void **tab_nlist, void *nlist, uint32_t size)
{
	static uint32_t	placed = 0;
	uint32_t		len[3];

	LEN_TAB = 0;
	placed += (placed >= size) ? (-placed) : 1;
	while (LEN_TAB < placed
		&& tab_nlist[LEN_TAB]
		&& sorted_text(STRING(tab_nlist[LEN_TAB]), STRING(nlist)))
		LEN_TAB++;
	if (tab_nlist[LEN_TAB])
	{
	 	LEN_SAVE = LEN_TAB;
	 	LEN_TAB = placed;
	 	while (LEN_TAB > LEN_SAVE)
	 	{
	 		tab_nlist[LEN_TAB] = tab_nlist[LEN_TAB - 1];
			--LEN_TAB;
		}
	}
	tab_nlist[LEN_TAB] = nlist;
	return (RETURN_SUCESS);
}

int		read_match_nlist(t_match match, void **tab_nlist)
{
	uint32_t		len;

	len = 0;
	printf("\n");
	while (len < SYMTAB->nsyms)
	{
		//printf()

		//printf("[%s]\n", &SYMTAB_STRING[((t_st_nlis_64*)(tab_nlist[len]))->n_strx]);
		len++;
	}
	(void)tab_nlist;
	return (RETURN_SUCESS);
}
int		read_match_command(t_match match)
{
	uint32_t		count_section;

	count_section = 0;
	SECTION = COMMAND + M_SIZEOF_SEGM;
	while (count_section++ < SEGMENT_NSECTS)
	{
		if (!read_match_section(match))
			return (RETURN_SUCESS);
		SECTION += M_SIZEOF_SECT;
	}
	return (RETURN_FAIL);
}

int		read_match_section(t_match match)
{
	if (same_text(SECTION_SECTNAME, TEXT_SECT)
		&& same_text(SECTION_SEGNAME, TEXT_SEG))
	{
		if (M_PROCESSOR == 64)
			return (read_text(match.header + SECTION_64->offset,
				SECTION_64->addr, SECTION_64->size, 16));
		else
			return (read_text(match.header + SECTION_32->offset,
				SECTION_32->addr, SECTION_32->size, 8));
	}
	return (RETURN_FAIL);
}
