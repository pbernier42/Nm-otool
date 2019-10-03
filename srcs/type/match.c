/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:17:18 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/30 19:17:19 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm_otool.h>

int		read_match_32(void *data, bool endian, t_eflags flag)
{
	t_match			match;

	match.header = data;
	match.lc_segment = LC_SEGMENT;
	match.ncmds = ((t_mh_head_32*)data)->ncmds;
	match.command = data + sizeof(t_mh_head_32);
	match.section = NULL;
	match.endian = endian;
	M_SIZEOF_SEGM = sizeof(t_mh_segm_32);
	M_SIZEOF_SECT = sizeof(t_mh_sect_32);
	M_ADDR_NSECTS_SEGM = 48;
	M_ADDR_SIZE = 8;
	match.flag = flag;
	return(read_match_file(match));
}

int		read_match_64(void *data, bool endian, t_eflags flag)
{
	t_match			match;

	match.header = data;
	match.lc_segment = LC_SEGMENT_64;
	match.ncmds = ((t_mh_head_64*)data)->ncmds;
	match.command = data + sizeof(t_mh_head_64);
	match.section = NULL;
	match.endian = endian;
	M_SIZEOF_SEGM = sizeof(t_mh_segm_64);
	M_SIZEOF_SECT = sizeof(t_mh_sect_64);
	M_ADDR_NSECTS_SEGM = 64;
	M_ADDR_SIZE = 16;
	match.flag = flag;
	return(read_match_file(match));
}

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
	return (error(ERROR_FILE___TEXT));
}
