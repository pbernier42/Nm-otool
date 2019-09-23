/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:24:55 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/03 17:24:56 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <unistd.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>

typedef unsigned long long		t_ull;

# define RETURN_SUCESS	0
# define RETURN_FAIL	-1

# define CHAR_HEXA	((char[16]){"0123456789abcdef"})

/*
**	count.c
*/

size_t		len_text(char *text);
short		size_number(t_ull number);

/*
**	print.c
*/

void		print_address(t_ull adress, short size, bool ox);
void		print_number(t_ull number);

#endif
