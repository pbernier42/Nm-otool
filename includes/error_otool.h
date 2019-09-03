/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:53:08 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/03 16:53:10 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_OTOOL_H
# define ERROR_OTOOL_H

# include <errno.h>
# include <ft_otool.h>

/*
**	error_otool.c
*/

typedef struct s_error		t_error;
typedef enum e_errno		e_errno;

enum						e_errno
{
	error_usage_wrong,
	error_file_permission,
	error_file_dont_exist,
	error_file_is_directory,
	error_file_unknown,
	error_file_close
};

struct						s_error
{
	char			*file;
	char			*text;
	e_errno			value;
};

# define E_PERM		error_file_permission
# define E_EXIS		error_file_dont_exist
# define E_DIRE		error_file_is_directory
# define E_UNKN		error_file_unknown
# define E_CLOS		error_file_close

# define T_PERM		"Permission denied"
# define T_EXIS		"No such file or directory"
# define T_DIRE		"Is a directory"
# define T_UNKN		"Unknown open error"
# define T_CLOS		"Didn't close"

# define ERROR_FILE_PERMISSION		((t_error){file, T_PERM, E_PERM})
# define ERROR_FILE_DONT_EXIST		((t_error){file, T_EXIS, E_EXIS})
# define ERROR_FILE_IS_DIRECTORY	((t_error){file, T_DIRE, E_DIRE})
# define ERROR_FILE_UNKNOWN			((t_error){file, T_UNKN, E_UNKN})
# define ERROR_FILE_CLOSE			((t_error){file, T_CLOS, E_CLOS})

int			error_usage(void);
t_error		error_file(int fd, char *file);
int			error_otool(t_error error);


#endif
