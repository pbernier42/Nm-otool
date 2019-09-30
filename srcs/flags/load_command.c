/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:05:57 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/30 19:05:58 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void 		print_header(void *data)
{
	t_mh_head_64	*mh_header;

	mh_header = data;
	write(1, "Mach header\n      magic cputype cpusubtype  caps    filetype "
		"ncmds sizeofcmds      flags\n ", 90);
	print_address(mh_header->magic, 8, true);
	write(1, CHAR_SPACE, 9 - size_number(mh_header->cputype));
	print_number(mh_header->cputype);
	write(1, CHAR_SPACE, 11 - size_number(mh_header->cpusubtype));
	print_number(mh_header->cpusubtype);
	write(1, CHAR_SPACE, 2);
	print_address(0, 2, true);
	write(1, CHAR_SPACE, 12 - size_number(mh_header->filetype));
	print_number(mh_header->filetype);
	write(1, CHAR_SPACE, 6 - size_number(mh_header->ncmds));
	print_number(mh_header->ncmds);
	write(1, CHAR_SPACE, 11 - size_number(mh_header->sizeofcmds));
	print_number(mh_header->sizeofcmds);
	write(1, CHAR_SPACE, 1);
	print_address(mh_header->flags, 8, true);
	write(1, "\n", 1);
}

void		print_section(void *data)
{
	t_mh_sect_64	*mh_section;

	mh_section = data;
	write(1, "Section\n  sectname ", 19);
	write(1, mh_section->sectname, 16);
	write(1, "\n   segname ", 12);
	write(1, mh_section->segname, 16);
	write(1, "\n      addr ", 12);
	print_address(mh_section->addr, 16, true);
	write(1, "\n      size ", 12);
	print_address(mh_section->size, 16, true);
	write(1, "\n    offset ", 12);
	print_number(mh_section->offset);
	write(1, "\n     align ", 12);
	print_number(mh_section->align);
	write(1, "\n    reloff ", 12);
	print_number(mh_section->reloff);
	write(1, "\n    nreloc ", 12);
	print_number(mh_section->nreloc);
	write(1, "\n     flags ", 12);
	print_address(mh_section->flags, 8, true);
	write(1, "\n reserved1 ", 12);
	print_number(mh_section->reserved1);
	write(1, "\n reserved2 ", 12);
	print_number(mh_section->reserved2);
	write(1, "\n", 1);
}

void 		print_command(void *data)
{
	static short	count = -1;
	t_mh_comm		*mh_commande;

	mh_commande = data;
	write(1, "Load command ", 14);
	//64 - 32 LC_
	if (mh_commande->cmd == LC_SEGMENT || mh_commande->cmd == LC_SEGMENT_64)
		count = -1;
	print_number(++count);
	write(1, "\n      cmd ", 11);
	print_number(mh_commande->cmd);
	write(1, "\n  cmdsize ", 11);
	print_number(mh_commande->cmdsize);
	write(1, "\n", 1);
	// A FINIR
	write(1, "\n", 1);
}
