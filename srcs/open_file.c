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

#include <nm_otool.h>

int		open_file(char *file, t_flags *flags)
{
	int			fd;
	struct stat buf;
	void		*data;
	int			ret;

	ERROR_INIT_FILE(file);
	if ((fd = open(file, O_RDONLY)) < 0)
		return (error(error_open(fd)));
	if (fstat(fd, &buf) != 0)
		return (error(ERROR_FILE_PERMISSION));
	if (S_ISDIR(buf.st_mode))
		return (error(ERROR_FILE_IS_DIRECTORY));
	data = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	ret = close(fd);
	if (data == MAP_FAILED)
		error(ERROR_ALLOC_MMAP);
	if (ret)
		return (error(ERROR_FILE_CLOSE));
	if (data == MAP_FAILED)
		return (RETURN_FAIL);
	(void)buf.st_size;
	if (type_file(file, data, flags))
		return (RETURN_FAIL);
	if (munmap(data, buf.st_size))
		return(error(ERROR_ALLOC_MUNMAP));
	return (RETURN_SUCESS);
}

int		type_file(char *file, void *data, t_flags *flags)
{
	uint32_t	*magic;
	short		i;
	t_eflags	flag;

	if (!data)
		return (error(ERROR_CORRUPT_EMPTY));
	magic = data;
	//printf("[%08.8x]\n", *magic);
	//return (RETURN_SUCESS);
	i = 0;
	while (i < (NUM_TYPE * 2) && *magic != TAB_MAGIC[i])
		++i;
	if (i == (NUM_TYPE * 2))
		return (error(ERROR_FILE_TYPE));
	while ((flag = what_flag((char *)flags)) != e_no_flags)
	{
		//TMP /!!
		if (flag != e_load_command)
		{
			if (flag != e_symbols_file)
			{
				write(1, file, len_text(file));
				write(1, ":\n", 2);
			}
			//printf("[%i][%i]\n", i, i % NUM_TYPE);
			if (TAB_FT[i % NUM_TYPE](data, (i >= NUM_TYPE) ? true : false, flag))
				return (RETURN_FAIL);
		}
	}
	return (RETURN_SUCESS);
}

t_eflags		what_flag(char *flags)
{
	t_eflags		flag;
	static t_flags	done = RESET_FLAGS;

	flag = 0;
	while (flag != e_no_flags
		&& (!flags[flag] || (flags[flag] && DONE_FLAGS[flag])))
		++flag;
	if (flag != e_no_flags && !(DONE_FLAGS[flag]))
		DONE_FLAGS[flag] = 1;
	if (flag == e_no_flags)
		done = RESET_FLAGS;
	return (flag);
}
