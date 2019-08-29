/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:23:04 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/29 16:23:05 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# include <stdio.h>

# include <stdbool.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <unistd.h>

typedef struct s_header		t_header;
typedef struct s_segment	t_segment;

struct						s_header
{
	unsigned int			magic;
	int						cputype;
	int						cpusubtype;
	unsigned int      		filetype;
	unsigned int      		ncmds;
	unsigned int      		sizeofcmds;
	unsigned int      		flags;
};

struct						s_segment
{
  unsigned int  cmd;
  unsigned int  cmdsize;
  char      	segname[16];
  unsigned int  vmaddr;
  unsigned int  vmsize;
  unsigned int  fileoff;
  unsigned int  filesize;
  int			maxprot;
  int			initprot;
  unsigned int  nsects;
  unsigned int  flags;
};


#endif
