/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:47:05 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/30 14:47:06 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <ft_otool.h>

void		print_section(void *data)
{
	t_mh_sect_64	*mh_section;

	mh_section = data;
	write(1, "Section\n  sectname ", 19);
	write(1, mh_section->sectname, 16);
	write(1, "\n   segname ", 12);
	write(1, mh_section->segname, 16);
	write(1, "\n      addr ", 12);
	print_address(mh_section->addr, 16);
	write(1, "\n      size ", 12);
	print_address(mh_section->size, 16);
	write(1, "\n    offset ", 12);
	print_number(mh_section->offset);
	write(1, "\n     align ", 12);
	print_number(mh_section->align);
	write(1, "\n    reloff ", 12);
	print_number(mh_section->reloff);
	write(1, "\n    nreloc ", 12);
	print_number(mh_section->nreloc);
	write(1, "\n     flags ", 12);
	print_address(mh_section->flags, 8);
	write(1, "\n reserved1 ", 12);
	print_number(mh_section->reserved1);
	write(1, "\n reserved2 ", 12);
	print_number(mh_section->reserved2);
	write(1, "\n", 1);
}

void 		print_header(void *data)
{
	t_mh_head_64	*mh_header;

	mh_header = data;
	write(1, "Mach header\n      magic cputype cpusubtype  caps    filetype "
		"ncmds sizeofcmds      flags\n ", 90);
	print_address(mh_header->magic, 8);
	write(1, CHAR_SPACE, 9 - size_number(mh_header->cputype));
	print_number(mh_header->cputype);
	write(1, CHAR_SPACE, 11 - size_number(mh_header->cpusubtype));
	print_number(mh_header->cpusubtype);
	write(1, CHAR_SPACE, 2);
	print_address(0, 2);
	write(1, CHAR_SPACE, 12 - size_number(mh_header->filetype));
	print_number(mh_header->filetype);
	write(1, CHAR_SPACE, 6 - size_number(mh_header->ncmds));
	print_number(mh_header->ncmds);
	write(1, CHAR_SPACE, 11 - size_number(mh_header->sizeofcmds));
	print_number(mh_header->sizeofcmds);
	write(1, CHAR_SPACE, 1);
	print_address(mh_header->flags, 8);
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

void	print_data(unsigned char data[16], short size)
{
 	char			ret[size * 3];
 	short			len;

 	len	= 0;
 	while (len < size)
 	{
 		//CHANGER CA  par CHAR_HEXA
 		// ret[(len * 3)] = HEXA_CHAR(data[len] / 16);
 		// ret[(len * 3) + 1] = HEXA_CHAR(data[len]);
 		// ret[(len * 3) + 2] = len != (size - 1) ? ' ' : '\n';
 		len++;
	}
 	write(1, ret, size * 3);
}
