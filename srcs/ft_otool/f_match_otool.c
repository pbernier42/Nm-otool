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

# define SYMBOL			((t_st_comm*)match.command)
# define NLIST			((t_st_nlis_64*)match.section)
# define SYMBOL_NSYMS	SYMBOL->nsyms
# define SYMBOL_CHAR	("UATDBC-SIW")
# define STRING			((char*)(match.header + SYMBOL->symoff + SYMBOL->strsize))

int		read_match_symtab(t_match match)
{
	uint32_t		count_symbol;

	count_symbol = 0;
	SECTION = match.header + SYMBOL->symoff;
	while (count_symbol++ < SYMBOL_NSYMS-)
	{
		printf("fonction = [%s]\n", STRING + NLIST->n_strx);
		printf("n_strx = [%u]\n", NLIST->n_strx);
		printf("n_type = [%hhu]\n", NLIST->n_type);
		printf("n_sect = [%hhu]\n", NLIST->n_sect);
		printf("n_desc = [%hd]\n", NLIST->n_desc);
		printf("n_value = [%llu]\n\n", NLIST->n_value);
		SECTION += sizeof(t_st_nlis_64);
	}
	return (0);
}

// printf("CMD__ = [%u]\nCMD_S = [%u]\nOFF_N = [%u]-\n"
// 	"NUMBE = [%u]\nOFF_S = [%u]-\nSTR_S = [%u]\n\n",
// 	SYMBOL->cmd, SYMBOL->cmdsize, SYMBOL->symoff,
// 	SYMBOL->nsyms, SYMBOL->stroff, SYMBOL->strsize);

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
		if (match.lc_segment == LC_SEGMENT_64)
			return (read_text(match.header + SECTION_64->offset,
				SECTION_64->addr, SECTION_64->size, 16));
		else
			return (read_text(match.header + SECTION_32->offset,
				SECTION_32->addr, SECTION_32->size, 8));
	}
	return (RETURN_FAIL);
}
