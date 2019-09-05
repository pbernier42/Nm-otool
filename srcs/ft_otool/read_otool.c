/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_otool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:11:40 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/05 12:11:43 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int		read_match_64(void *data, t_ull size_file, bool endian, t_eflags flag)
{
	uint32_t		count[2];
	void			*command;
	s_mach_sect_64	*section;

	//ATTENTO CORROMPU
	//endian
	COUNT_COMMAND = 0;
	if (flag == e_load_command)
		print_header(data);
	command = data + SIZE_MH_HEAD_64;
	while (COUNT_COMMAND++ < ((t_mh_head_64*)data)->ncmds)
	{
		COUNT_SECTION = 0;
		if (flag == e_load_command)
			print_command(command);
		if (((t_mh_comm*)command)->cmd == LC_SEGMENT_64)
		{
			section = command + SIZE_MH_SEGM_64;
			while (COUNT_SECTION++ < ((t_mh_segm_64*)command)->nsects)
			{
				if (flag == e_text_section
					&& same_text(section->sectname, TEXT_SECT)
					&& same_text(section->segname, TEXT_SEG))
					return (read_text(data + section->offset, section->size));
				if (flag == e_load_command)
					print_section(section);
				++section;
			}
		}
		command += ((t_mh_comm*)command)->cmdsize;
	}
	if (flag == e_text_section)
		return (-1);

	(void)size_file;
	(void)endian;
	return (RETURN_SUCESS);
}

int		read_text(void *data, t_ull size)
{
	t_ull	address;

	adress = 0;
	while (adress < size)
	{
		print_address(adress, 8);
		print_data(&(data + address),
			(size - address) <= 16 ? (size - address) : 16);
		adress += 16;
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
