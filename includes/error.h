/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:53:08 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/03 16:53:10 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>

/*
**	error_otool.c
*/

typedef struct s_error		t_error;
typedef enum e_fonction		e_fonction;
typedef enum e_errno		e_errno;

enum						e_fonction
{
	ft_null,
	ft_otool,
	ft_nm
};

enum						e_errno
{
	error_init_fonction,
	error_init_file,
	error_usage_fonction,
	error_usage_wrong,
	error_usage_no_file,
	error_usage_flag,
	error_usage_unknow_char,
	error_file_permission,
	error_file_dont_exist,
	error_file_is_directory,
	error_file_unknown,
	error_file_close,
	error_file_type,
	error_file_text,
	error_alloc_mmap,
	error_alloc_munmap,
	error_corrupt_empty
};

struct						s_error
{
	char			*text;
	e_errno			value;
	char			__pad[4];
};

# define E__PAD					{0, 0, 0, 0}
# define S_FILL(text, error)	((t_error){text, error, E__PAD})

# define E_I_FT		error_init_fonction
# define E_I_FI		error_init_file
# define E_NO_F		error_usage_no_file
# define E_FLAG		error_usage_flag
# define E_UN_C		error_usage_unknow_char
# define E_PERM		error_file_permission
# define E_EXIS		error_file_dont_exist
# define E_DIRE		error_file_is_directory
# define E_UNKN		error_file_unknown
# define E_CLOS		error_file_close
# define E_TYPE		error_file_type
# define E_TEXT		error_file_text
# define E_MMAP		error_alloc_mmap
# define E_MUNM		error_alloc_munmap
# define E_EMPT		error_corrupt_empty

# define T_NO_F		"at least one file must be specified"
# define T_FLAG		"one of -" CHAR_FLAGS " must be specified"
# define T_UN_C		"unknown char"
# define T_PERM		"Permission denied"
# define T_EXIS		"No such file or directory"
# define T_DIRE		"Is a directory"
# define T_UNKN		"Unknown open error"
# define T_CLOS		"Didn't close"
# define T_TYPE		"is not an object file"
# define T_TEXT		"(" TEXT_SEG "," TEXT_SECT ") not found"
# define T_MMAP		"Fail to mmap"
# define T_MUNM		"Fail to munmap"
# define T_EMPT		"Empty file"

# define ERROR_USAGE_NO_FILE		S_FILL(T_NO_F, E_NO_F)
# define ERROR_USAGE_FLAG			S_FILL(T_FLAG, E_FLAG)
# define ERROR_USAGE_UNKNOWN_CHAR	S_FILL(T_UN_C, E_UN_C)
# define ERROR_FILE_PERMISSION		S_FILL(T_PERM, E_PERM)
# define ERROR_FILE_DONT_EXIST		S_FILL(T_EXIS, E_EXIS)
# define ERROR_FILE_IS_DIRECTORY	S_FILL(T_DIRE, E_DIRE)
# define ERROR_FILE_UNKNOWN			S_FILL(T_UNKN, E_UNKN)
# define ERROR_FILE_CLOSE			S_FILL(T_CLOS, E_CLOS)
# define ERROR_FILE_TYPE			S_FILL(T_TYPE, E_TYPE)
# define ERROR_FILE___TEXT			S_FILL(T_TEXT, E_TEXT)
# define ERROR_ALLOC_MMAP			S_FILL(T_MMAP, E_MMAP)
# define ERROR_ALLOC_MUNMAP			S_FILL(T_MUNM, E_MUNM)
# define ERROR_CORRUPT_EMPTY		S_FILL(T_EMPT, E_EMPT)

# define ERROR_INIT_FONCTION(text)	error(S_FILL(text, E_I_FT))
# define ERROR_INIT_FILE(file)		error(S_FILL(file, E_I_FI))

int			error_usage(e_fonction fonction);
t_error		error_open(int fd);
int			error(t_error error);
int			error_init(char **fonction, char **file, t_error error);
void		error_e_un_c(char unknow, char *argv);

#endif
