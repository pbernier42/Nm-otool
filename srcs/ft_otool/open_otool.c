/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_otool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:12:29 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/30 16:12:31 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_otool.h>

int		open_file(char *file, t_flags *flags)
{
	int			fd;
	struct stat buf;
	void		*data;
	int			ret;

	INIT(file);
	// printf("[%d][%d]\n", flags->text_section, flags->load_command);
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
	if (type_file(file, data, buf.st_size, flags))
		return (RETURN_FAIL);
	if (munmap(data, buf.st_size))
		return(error_otool(ERROR_ALLOC_MUNMAP));
	return (RETURN_SUCESS);
}

int		type_file(char *file, void *data, t_ull size_file, t_flags *flags)
{
	uint32_t	*magic;
	short		i;
	t_eflags	flag;

	// printf("[%d][%d]\n", flags->text_section, flags->load_command);
	if (!data)
		return (error_otool(ERROR_CORRUPT_EMPTY));
	magic = data;
	i = 0;
	while (i < 8 && *magic != TAB_MAGIC[i])
		++i;
	if (i == 8)
		return (error_otool(ERROR_FILE_TYPE));

	while ((flag = what_flag((char *)flags)) != e_no_flags)
	{
		write(1, file, len_text(file));
		write(1, ":\n", 2);

		printf("[%d][%d]\n", i, i % 4);
		if (TAB_FT[i % 4](data, size_file, (i >= 4) ? true : false, flag))
			return (RETURN_FAIL);
	}
	return (RETURN_SUCESS);
}

t_eflags		what_flag(char *flags)
{
	t_eflags	flag;

	flag = 0;
	while (flag != e_no_flags && !flags[flag])
		++flag;
	if (flag != e_no_flags && flags[flag])
		flags[flag] = 0;
	return (flag);
}
