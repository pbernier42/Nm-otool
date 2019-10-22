/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_section.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:06:23 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/30 19:06:24 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm_otool.h>

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
		if (M_ADDR_SIZE == 16)
			return (read_match_text(match.header + SECTION_64->offset,
				SECTION_64->addr, SECTION_64->size, M_ADDR_SIZE));
		else
			return (read_match_text(match.header + SECTION_32->offset,
				SECTION_32->addr, SECTION_32->size, M_ADDR_SIZE));
	}
	return (RETURN_FAIL);
}

int		read_match_text(void *data, t_ull offset, t_ull size_file, short size)
{
	t_ull	count;

	count = 0;
	write(1, "Contents of (" TEXT_SEG "," TEXT_SECT ") section\n", 36);
	while (count < size_file)
	{
		print_address(offset, size, false);
		write(1, "\t", 1);
		print_data((data + count),
			(size_file - count) <= 16 ? (size_file - count) : 16);
		count += 16;
		offset += 16;
	}
	return (RETURN_SUCESS);
}

void	print_data(unsigned char data[16], short size)
{
 	char			ret[(size * 3) + 1];
 	short			len;

 	len	= 0;
 	while (len < size)
 	{
		ret[(len * 3)] = CHAR_HEXA[data[len] / 16];
 		ret[(len * 3) + 1] = CHAR_HEXA[data[len] % 16];
 		ret[(len * 3) + 2] = ' ';
 		len++;
	}
	ret[(size * 3)] = '\n';
 	write(1, ret, (size * 3) + 1);
}
