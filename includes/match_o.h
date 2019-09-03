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

# include <ft_otool.h>
# include <stdint.h>

#define MH_MAGIC     0xfeedface    /* the mach magic number */
#define MH_CIGAM     0xcefaedfe    /* NXSwapInt(MH_MAGIC) */

#define MH_MAGIC_64  0xfeedfacf    /* the 64-bit mach magic number */
#define MH_CIGAM_64  0xcffaedfe    /* NXSwapInt(MH_MAGIC_64) */

#define FAT_MAGIC    0xcafebabe    /* the fat magic number */
#define FAT_CIGAM    0xbebafeca    /* NXSwapLong(FAT_MAGIC) */

#define FAT_MAGIC_64 0xcafebabf    /* the 64-bit fat magic number */
#define FAT_CIGAM_64 0xbfbafeca    /* NXSwapLong(FAT_MAGIC_64) */


struct				mach_header	/* struct mach_header_64 for 64-bit */
{
	uint32_t		magic;		/* mach magic number identifier */
	int				cputype;	/* cpu specifier */
	int				cpusubtype;	/* machine specifier */
	uint32_t      	filetype;	/* type of file */
	uint32_t      	ncmds;		/* number of load commands */
	uint32_t      	sizeofcmds; /* the size of all the load commands */
	uint32_t      	flags;		/* flags */
	uint32_t		reserved;	/* reserved */ 							//exist que pour 64
};

struct 				load_command /* load_command header */
{
	uint32_t		cmd;        /* type of load command */
    uint32_t		cmdsize;    /* total size of command in bytes */
};

struct 				fat_header
{
	uint32_t		magic;      /* FAT_MAGIC or FAT_MAGIC_64 */
    uint32_t		nfat_arch;  /* number of structs that follow */
};

struct 				fat_arch	/* struct fat_arch_64 for 64-bit*/
{
	int				cputype;    /* cpu specifier (int) */
	int				cpusubtype; /* machine specifier (int) */
	// uint32_t        offset;     /* file offset to this object file *///exist que pour 32
	// uint32_t        size;       /* size of this object file */		//exist que pour 32
	uint64_t        offset;     /* file offset to this object file */	//exist que pour 64
	uint64_t        size;       /* size of this object file */			//exist que pour 64
    uint32_t        align;      /* alignment as a power of 2 */
	uint32_t        reserved;   /* reserved */ 							//exist que pour 64
};

struct				segment_command/* struct segment_command_64 for 64-bit */
{
	uint32_t        cmd;         /* LC_SEGMENT or LC_SEGMENT_64 */
    uint32_t        cmdsize;     /* includes sizeof section structs */
    char            segname[16]; /* segment name */
	//uint32_t        vmaddr;      /* memory address of this segment */	//exist que pour 32
	//uint32_t        vmsize;      /* memory size of this segment */	//exist que pour 32
	//uint32_t        fileoff;     /* file offset of this segment */	//exist que pour 32
	//uint32_t        filesize;    /* amount to map from the file */	//exist que pour 32
	uint64_t        vmaddr;      /* memory address of this segment */	//exist que pour 32
	uint64_t        vmsize;      /* memory size of this segment */		//exist que pour 64
	uint64_t        fileoff;     /* file offset of this segment */		//exist que pour 64
	uint64_t        filesize;    /* amount to map from the file */		//exist que pour 64
    int				maxprot;     /* maximum VM protection */
    int				initprot;    /* initial VM protection */
    uint32_t        nsects;      /* number of sections in segment */
    uint32_t        flags;       /* flags */
};

struct				section
{                   /* struct section_64 for 64-bit */
    char            sectname[16]; /* name of this section */
    char            segname[16];  /* segment this section goes in */
 	uint64_t        addr;         /* for memory address of this section *///exist que pour 64
	uint64_t        size;         /* for size in bytes of this section */ //exist que pour 64
	//uint32_t        addr;         /* for memory address of this section //exist que pour 32
	//uint32_t        size;         /* for size in bytes of this section  //exist que pour 32
    uint32_t        offset;       /* file offset of this section */
    uint32_t        align;        /* section alignment (power of 2) */
    uint32_t        reloff;       /* file offset of relocation entries */
    uint32_t        nreloc;       /* number of relocation entries */
    uint32_t        flags;        /* flags (section type and attributes)*/
    uint32_t        reserved1;    /* reserved (for offset or index) */
    uint32_t        reserved2;    /* reserved (for count or sizeof) */
	uint32_t        reserved3;    /* reserved */							//exist que pour 32
};

#endif
