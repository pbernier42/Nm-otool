/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_o.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:02:46 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/30 16:02:47 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATCH_O_H
# define FT_MATCH_O_H

# include <ft_nm_otool.h>

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
	unsigned int  			cmd;
	unsigned int			cmdsize;
	char					segname[16];
	unsigned int			vmaddr;
	unsigned int			vmsize;
	unsigned int			fileoff;
	unsigned int			filesize;
	int						maxprot;
	int						initprot;
	unsigned int			nsects;
	unsigned int			flags;
};

#endif
