/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:17:10 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/30 19:17:11 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm_otool.h>

int		read_fat_32(void *data, bool endian, t_eflags flag)
{
	t_fat	fat;

	fat.header = data;
	fat.arch = data + sizeof(t_ft_head*);
	fat.sizeof_arch = sizeof(t_ft_arch_32*);
	fat.endian = endian;
	fat.flag = flag;
	return (read_fat_file(fat));
}

int		read_fat_64(void *data, bool endian, t_eflags flag)
{
	t_fat	fat;

	fat.header = data;
	fat.arch = data + sizeof(t_ft_head*);
	fat.sizeof_arch = sizeof(t_ft_arch_64*);
	fat.endian = endian;
	fat.flag = flag;
	return (read_fat_file(fat));
}

int		read_fat_file(t_fat fat)
{
	uint32_t		count_arch;

	count_arch = ((t_ft_head*)(fat.header))->nfat_arch;
	while (count_arch--)
	{
		if (OFFSET == MH_MAGIC)
			return (read_match_32(&OFFSET, fat.endian, fat.flag));
		if (OFFSET == MH_MAGIC_64)
			return (read_match_64(&OFFSET, fat.endian, fat.flag));
		fat.arch += fat.sizeof_arch;
	}
	//error pas trouvé magic
	return (RETURN_FAIL);
}
