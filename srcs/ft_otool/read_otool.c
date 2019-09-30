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

int		read_match_nlist(t_match match, void **tab_nlist)
{
	uint32_t		len;
	unsigned char	bit;
	char			type;

	len = 0;
	while (len < SYMTAB->nsyms)
	{
		bit = (N_TYPE(tab_nlist[len]) & 0x0e);
		if (bit != 0x0 && bit != 0x2)
		 	print_address(N_VALUE(tab_nlist[len]), M_ADDR_SIZE, false);
		else
			write(1, CHAR_SPACE, M_ADDR_SIZE);
		write(1, " ", 1);
		type = '?';
		if (read_match_ntype(match, tab_nlist[len], &type))
			return (-1); //TMP
		write(1, &type, 1);
		write(1, " ", 1);
		write(1, STRING(tab_nlist[len]), len_text(STRING(tab_nlist[len])));
		write(1, "\n", 1);
		len++;
	}
	return (RETURN_SUCESS);
}

int			read_match_ntype(t_match match, void *nlist, char *type)
{
	short			len;
	unsigned char	bit;

	if (N_DESC(nlist))
	{
		*type = 'W';
		return(RETURN_SUCESS);
	}
	if ((bit = (N_TYPE(nlist) & 0xe0)))
		return (RETURN_SUCESS);
	if (!(bit = (N_TYPE(nlist) & 0x0e)))
		*type = N_VALUE(nlist) ? 'c' : 'u';
	len = 0;
	while ((bit) && len < 4)
		if (bit == ((char[4]){0x2, 0xe, 0xc, 0xa})[len++])
			*type = ((char[4]){'a', what_sectname(SECTNAME(nlist)), 'u', 'i'})[len - 1];
	if ((bit = (N_TYPE(nlist) & 0x01)) && *type >= 'a' && *type <= 'z')
	 		*type -= ('a' - 'A');
	return (RETURN_SUCESS);
}

char		what_sectname(char text[16])
{
	short		len;

	len = 0;
	while (len < 3)
		if (same_text(
			(((char*[3]){TEXT_SECT, "__data", "__bss"})[len++]), text))
			return (((char[3]){'t', 'd', 'b'})[len - 1]);
	//error sectname
	return ('s');
}
