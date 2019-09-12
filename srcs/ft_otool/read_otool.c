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

//ATTENTO CORROMPU
//endian



int		read_match_64(void *data, bool endian, t_eflags flag)
{
	uint32_t		count[2];
	void			*command;
	t_mh_sect_64	*section;


	COUNT_COMMAND = 0;
	command = data + SIZE_MH_HEAD_64;
	while (COUNT_COMMAND++ < ((t_mh_head_64*)data)->ncmds)
	{
		COUNT_SECTION = 0;
		if (((t_mh_comm*)command)->cmd == LC_SEGMENT_64)
		{
			section = command + SIZE_MH_SEGM_64;
			while (COUNT_SECTION++ < ((t_mh_segm_64*)command)->nsects)
			{
				if (same_text(section->sectname, TEXT_SECT)
					&& same_text(section->segname, TEXT_SEG))
					return (read_text(data + section->offset,
						section->addr, section->size));
				++section;
			}
		}
		command += ((t_mh_comm*)command)->cmdsize;
	}
	(void)endian;
	(void)flag;
	return (error_otool(ERROR_FILE___TEXT));
}

// int		read_match_32(void *data, t_ull size_file, bool endian, t_eflags flag)
// {
// 	uint32_t		count[2];
// 	void			*command;
// 	t_mh_sect_32	*section;
//
// 	//ATTENTO CORROMPU
// 	//endian
// 	COUNT_COMMAND = 0;
//
// 	command = data + sizeof(t_mh_head_32);
// 	while (COUNT_COMMAND++ < ((t_mh_head_64*)data)->ncmds)
// 	{
// 		COUNT_SECTION = 0;
// 		//printf("[%u]\n", ((t_mh_comm*)command)->cmd);
//
// 		if (((t_mh_comm*)command)->cmd == LC_SEGMENT)
// 		{
// 			section = command + sizeof(t_mh_segm_32);
// 			while (COUNT_SECTION++ < ((t_mh_segm_32*)command)->nsects)
// 			{
// 				printf("[%u]\n", COUNT_SECTION);
// 				if (flag == e_text_section
// 					&& same_text(section->sectname, TEXT_SECT)
// 					&& same_text(section->segname, TEXT_SEG))
// 					return (read_text(data + section->offset,
// 						section->addr, section->size));
// 				++section;
// 			}
// 		}
// 		command += ((t_mh_comm*)command)->cmdsize;
// 	}
// 	if (flag == e_text_section)
// 		return (error_otool(ERROR_FILE___TEXT));
//
// 	(void)size_file;
// 	(void)endian;
// 	return (RETURN_SUCESS);
// }
//
//
// int		read_fat_64(void *data, t_ull size_file, bool endian, t_eflags flag)
// {
// 	uint32_t		count[2];
//
// 	//ATTENTO CORROMPU
// 	//endian
// 	COUNT_COMMAND = 0;
// 	if (flag == e_load_command)
// 		print_header(data);
//
//
// 	printf("?[%d]\n", endian);
// 	(void)data;
// 	(void)flag;
// 	(void)size_file;
// 	(void)endian;
// 	return (RETURN_SUCESS);
// }


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
	// printf("[%s]\n", text);
	while (text[i] == check[i] && check[i] && i < 16)
		++i;
	return ((i == 16 || !check[i]) ? true : false);
}
