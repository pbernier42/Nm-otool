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

#include <utils.h>

//ATTENTO CORROMPU
//endian
int		read_match_file(t_match match)
{
	uint32_t		count_command;

	count_command = 0;
	while (count_command++ < match.ncmds)
	{
		if (FLAG == e_load_command
			&& match.command->cmd == LC_SYMTAB
			&& !read_symtab(match))
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

int		read_text(void *data, t_ull offset, t_ull size)
{
	t_ull	count;

	count = 0;
	write(1, "Contents of (" TEXT_SEG "," TEXT_SECT ") section\n", 36);
	while (count < size)
	{
		print_address(offset, 16, false);
		write(1, "\t", 1);
		print_data((data + count),
			(size - count) <= 16 ? (size - count) : 16);
		count += 16;
		offset += 16;
	}
	return (RETURN_SUCESS);
}

bool		same_text(char text[16], char check[16])
{
	short	i;

	i = 0;
	while (text[i] == check[i] && check[i] && i < 16)
		++i;
	return ((i == 16 || !check[i]) ? true : false);
}