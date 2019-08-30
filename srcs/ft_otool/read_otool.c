/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_otool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:12:29 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/30 16:12:31 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_nm_otool.h>

bool	read_file(char *file)
{
	int				fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERROR);
	read_header(fd);
	read_data(fd);
	if (close(fd) == -1)
		return (ERROR);
	return (1);
}

void		read_header(int fd)
{
	unsigned int	count;
	char			buff[64];

	read(fd, buff, SIZE_HEADER);
	count = 0;
	//while (count++ < header.ncmds)
	// {
	printf("%zd\n", read(fd, buff, SIZE_SEGMENT));
	// }
	printf("?\n");
	// printf("magic\t\t= [%u]\ncputype\t\t= [%i]\ncpusubtype\t= [%i]\nfiletype\t= [%u]\nncmds\t\t= [%u]\nsizeofcmds\t= [%u]\nflags\t\t= [%u]\n\n",
	//  	 	header.magic, header.cputype, header.cpusubtype, header.filetype, header.ncmds, header.sizeofcmds, header.flags);
}

void		read_data(int fd)
{
	int				len;
	unsigned char	buff[BUFF];
	long long		count;

	count = 0;
	while ((len = read(fd, buff, BUFF)) > 0)
	{
		print_count(count);
		count += 16;
		print_data(buff, len);
	}
}

// void	tmp(int fd, int len, unsigned char buff[BUFF], long long count)
// {
// 	t_header	tmp[1];
// 	int			q = 0;
// 	t_segment	seg[1];
// 	//read(fd, buff, sizeof(t_header));
// 	read(fd, tmp, 32);
//
//
// 	while (q++ < 8)
// 	{
// 		read(fd, seg, 64);
// 		printf("%d\n", q);
// 		printf("cmd\t\t= [%u]\ncmdsize\t\t= [%u]\nsegname\t\t= [%s]\nvmaddr\t\t= [%u]\n"
// 		"vmsize\t\t= [%u]\nfileoff\t\t= [%u]\nfilesize\t= [%u]\nmaxprot\t\t= [%i]\n"
// 		"initprot\t= [%i]\nnsects\t\t= [%u]\nflags\t\t= [%u]\n\n",
// 		seg[0].cmd, seg[0].cmdsize, seg[0].segname, seg[0].vmaddr,
// 		seg[0].vmsize, seg[0].fileoff, seg[0].filesize, seg[0].maxprot,
// 		seg[0].initprot, seg[0].nsects, seg[0].flags);
// 	//	seg[0] = ((t_segment){0, 0, 0, 0, 0, 0, 0, 0, 0});
// 	}
// 	(void)fd;
// 	(void)len;
// 	(void)buff;
// 	(void)count;
// }
