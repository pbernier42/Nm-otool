/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:33:32 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/03 15:33:35 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <ft_otool.h>

int		error_usage()
{
	errno = error_usage_wrong;
	write(1, "Usage: /ft_otool <object file> ...\n", 35);
	return (RETURN_FAIL);
}

t_error		error_file(int fd, char *file)
{
	struct stat buf;

	if (fd == -1 && errno == EACCES)
		return (ERROR_FILE_PERMISSION);
	else if (fd == -1)
		return (ERROR_FILE_DONT_EXIST);
	if (fstat(fd, &buf) != 0)
		return (ERROR_FILE_PERMISSION);
	if (S_ISDIR(buf.st_mode))
		return (ERROR_FILE_IS_DIRECTORY);
	return (ERROR_FILE_UNKNOWN);
}

int		error_otool(t_error error)
{
	errno = error.value;
	write(2, "/ft_otool: '", 12);
	write(2, error.file, len_text(error.file));
	write(2, "': ", 3);
	write(2, error.text, len_text(error.text));
	write(2, "\n", 1);
	return (RETURN_FAIL);
}
