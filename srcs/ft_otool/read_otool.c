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
	match.flag = flag;
	return(read_match_file(match));
}


int		read_text(void *data, t_ull offset, t_ull size_file, short size)
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


bool		same_text(char text[16], char check[16])
{
	short	i;

	i = 0;
	while (text[i] == check[i] && check[i] && i < 16)
		++i;
	return ((i == 16 || !check[i]) ? true : false);
}
