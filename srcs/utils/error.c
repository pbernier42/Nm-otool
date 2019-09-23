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

# include <utils.h>

int		error_usage()
{
	errno = error_usage_wrong;
	write(1, "Usage: /ft_otool <object file> ...\n", 35);
	return (RETURN_FAIL);
}

t_error		error_open(int fd)
{
	if (fd == -1 && errno == EACCES)
		return (ERROR_FILE_PERMISSION);
	else if (fd == -1)
		return (ERROR_FILE_DONT_EXIST);
	return (ERROR_FILE_UNKNOWN);
}

int		error_otool(t_error error)
{
	static char	*file = NULL;

	if (error.value == error_init)
	{
		file = error.text;
		return (RETURN_SUCESS);
	}
	errno = error.value;
	if (error.value >= error_corrupt_empty)
		write(2, "corrupt: /ft_otool: ", 21);
	else if (error.value != error_file_type)
		write(2, "error: /ft_otool: ", 19);
	if (file)
	{
		if (error.value != error_file_type)
			write(2, "'", 1);
		write(2, file, len_text(file));
		if (error.value != error_file_type)
			write(2, "'", 1);
		write(2, ": ", 2);
	}
	write(2, error.text, len_text(error.text));
	if (error.value != error_usage_unknow_char)
		write(2, "\n", 1);
	return (RETURN_FAIL);
}

void	error_e_un_c(char unknow, char *argv)
{
	write(2, " `", 2);
	write(2, &unknow, 1);
	write(2, "' in flag ", 10);
	write(2, argv, len_text(argv));
	write(2, "\n", 1);
}
