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

#include <ft_otool.h>

int		open_file(char *file)
{
	int			fd;
	struct stat buf;
	void		*data;
	int			ret;

	INIT(file);
	if ((fd = open(file, O_RDONLY)) < 0)
		return (error_otool(error_open(fd)));
	if (fstat(fd, &buf) != 0)
		return (error_otool(ERROR_FILE_PERMISSION));
	if (S_ISDIR(buf.st_mode))
		return (error_otool(ERROR_FILE_IS_DIRECTORY));
	data = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	ret = close(fd);
	if (data == MAP_FAILED)
		error_otool(ERROR_ALLOC_MMAP);
	if (ret)
		return (error_otool(ERROR_FILE_CLOSE));
	if (data == MAP_FAILED)
		return (RETURN_FAIL);
	if (read_file(data, buf.st_size))
		return (RETURN_FAIL);
	if (munmap(data, buf.st_size))
		return(error_otool(ERROR_ALLOC_MUNMAP));
	return (RETURN_SUCESS);
}

int		read_file(void *data, unsigned long long size_file)
{
	uint32_t	*magic;
	bool		endian;

	if (!data)
		return (error_otool(ERROR_CORRUPT_EMPTY));
	magic = data;
	endian = (*magic == MH_CIGAM || *magic == MH_CIGAM_64
		|| *magic == FAT_CIGAM || *magic == FAT_CIGAM_64) ? true : false;

	if (*magic == MH_MAGIC || *magic == MH_CIGAM)
		printf("MATCH_O\n");
	else if (*magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
		printf("MATCH_O 64\n");
	else if (*magic == FAT_MAGIC || *magic == FAT_CIGAM)
		printf("FAT\n");
	else if (*magic == FAT_MAGIC_64 || *magic == FAT_CIGAM_64)
		printf("FAT 64\n");
	else
		return (error_otool(ERROR_FILE_TYPE));

	(void)size_file;
	return (RETURN_SUCESS);
}
