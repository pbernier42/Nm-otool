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

# include <error.h>
# include <nm_otool.h>
# include <utils.h>

int		error_usage(e_fonction fonction)
{
	if (!fonction)
	{
		errno = error_usage_fonction;
		write(2, "error: Executable's name must be", 32);
		write(2, "\'ft_nm\' or \'ft_otool\'\n", 25);
		return (RETURN_FAIL);
	}
	errno = error_usage_wrong;
	write(2, "Usage: ", 7);
	if (fonction == ft_otool)
	{
		write(2, "ft_otool [-", 11);
		write(2, CHAR_FLAGS, NUMBER_FLAGS);
		write(2, "]", 1);
	}
	else
		write(2, "ft_nm", 5);
	write(2, " <object file> ...\n", 19);
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

int		error(t_error error)
{
	static char	*file = NULL;
	static char	*fonction = NULL;

	if (!error_init(&fonction, &file, error))
		return (RETURN_SUCESS);
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

int		error_init(char **fonction, char **file, t_error error)
{
	if (error.value == error_init_fonction)
		(*fonction) = error.text;
	else if (error.value == error_init_file)
		(*file) = error.text;
	else
		return (RETURN_FAIL);
	return (RETURN_SUCESS);
}

void	error_e_un_c(char unknow, char *argv)
{
	write(2, " `", 2);
	write(2, &unknow, 1);
	write(2, "' in flag ", 10);
	write(2, argv, len_text(argv));
	write(2, "\n", 1);
}
