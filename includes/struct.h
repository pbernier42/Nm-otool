/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:02:46 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/30 16:02:47 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdint.h>
# include <utils.h>

# define MH_MAGIC    	0xfeedface
# define MH_CIGAM    	0xcefaedfe

# define MH_MAGIC_64  	0xfeedfacf
# define MH_CIGAM_64  	0xcffaedfe

# define FAT_MAGIC   	0xcafebabe
# define FAT_CIGAM    	0xbebafeca

# define FAT_MAGIC_64	0xcafebabf
# define FAT_CIGAM_64	0xbfbafeca

# define ARC_MAGIC		0x213c6172
# define ARC_CIGAM		0x72613c21


typedef struct s_mach_head_32		t_mh_head_32;
typedef struct s_mach_head_64		t_mh_head_64;
typedef struct s_mach_comm			t_mh_comm;

typedef struct s_mach_segm_32		t_mh_segm_32;
typedef struct s_mach_segm_64		t_mh_segm_64;
typedef struct s_mach_sect_32		t_mh_sect_32;
typedef struct s_mach_sect_64		t_mh_sect_64;

typedef struct s_fat_head			t_ft_head;
typedef struct s_fat_arch_32		t_ft_arch_32;
typedef struct s_fat_arch_64		t_ft_arch_64;

typedef struct s_symt_comm			t_st_comm;
typedef struct s_symt_nlis_64		t_st_nlis_64;

struct				s_mach_head_32	/* struct mach_header_64 for 64-bit */
{
	uint32_t		magic;		/* mach magic number identifier */
	int				cputype;	/* cpu specifier */
	int				cpusubtype;	/* machine specifier */
	uint32_t      	filetype;	/* type of file */
	uint32_t      	ncmds;		/* number of load commands */
	uint32_t      	sizeofcmds; /* the size of all the load commands */
	uint32_t      	flags;
};

struct				s_mach_head_64	/* struct mach_header_64 for 64-bit */
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

struct 				s_mach_comm/* load_command header */
{
	uint32_t		cmd;        /* type of load command */
    uint32_t		cmdsize;    /* total size of command in bytes */
};

struct				s_symt_comm
{
    uint32_t        cmd;        /* LC_SYMTAB */
    uint32_t        cmdsize;    /* sizeof(struct symtab_command) */
    uint32_t        symoff;     /* symbol table offset (nlist array) */
    uint32_t        nsyms;      /* number of symbol table entries */
    uint32_t        stroff;     /* string table offset */
    uint32_t        strsize;    /* string table size in bytes */
};

struct				s_symt_nlis_64
{                   /* struct nlist_64 for 64-bit */
    uint32_t		n_strx;     /* index into the string table (union n_un) */
    uint8_t         n_type;     /* type flag, see below */
    uint8_t         n_sect;     /* section number or NO_SECT */
    int16_t         n_desc;     /* see <mach-o/stab.h> */
	uint64_t        n_value;    /* value of this symbol (or stab offset) */
};

// struct				s_nlist_32
// {                   /* struct nlist_64 for 64-bit */
//     union           n_un:       /* union with char *n_name for 32-bit */
//         uint32_t    n_strx;     /* index into the string table (union n_un) */
//     uint8_t         n_type;     /* type flag, see below */
//     uint8_t         n_sect;     /* section number or NO_SECT */
//     int16_t         n_desc;     /* see <mach-o/stab.h> */
// _32 uint32_t        n_value;    /* value of this symbol (or stab offset) */
// _64 uint64_t        n_value;    /* value of this symbol (or stab offset) */
// };


struct				s_mach_segm_32
{
	uint32_t        cmd;         /* LC_SEGMENT or LC_SEGMENT_64 */
    uint32_t        cmdsize;     /* includes sizeof section structs */
    char            segname[16]; /* segment name */
	uint32_t        vmaddr;      /* memory address of this segment */	//exist que pour 32
	uint32_t        vmsize;      /* memory size of this segment */	//exist que pour 32
	uint32_t        fileoff;     /* file offset of this segment */	//exist que pour 32
	uint32_t        filesize;    /* amount to map from the file */	//exist que pour 32
    int				maxprot;     /* maximum VM protection */
    int				initprot;    /* initial VM protection */
    uint32_t        nsects;      /* number of sections in segment */
    uint32_t        flags;       /* flags */
};

struct				s_mach_segm_64/* struct segment_command_64 for 64-bit */
{
	uint32_t        cmd;         /* LC_SEGMENT or LC_SEGMENT_64 */
    uint32_t        cmdsize;     /* includes sizeof section structs */
    char            segname[16]; /* segment name */
	uint64_t        vmaddr;      /* memory address of this segment */	//exist que pour 64
	uint64_t        vmsize;      /* memory size of this segment */		//exist que pour 64
	uint64_t        fileoff;     /* file offset of this segment */		//exist que pour 64
	uint64_t        filesize;    /* amount to map from the file */		//exist que pour 64
    int				maxprot;     /* maximum VM protection */
    int				initprot;    /* initial VM protection */
    uint32_t        nsects;      /* number of sections in segment */
    uint32_t        flags;       /* flags */
};

struct				s_mach_sect_32
{
    char            sectname[16]; /* name of this section */
    char            segname[16];  /* segment this section goes in */
	uint32_t        addr;         /* for memory address of this section*/
	uint32_t        size;         /* for size in bytes of this section */
    uint32_t        offset;       /* file offset of this section */
    uint32_t        align;        /* section alignment (power of 2) */
    uint32_t        reloff;       /* file offset of relocation entries */
    uint32_t        nreloc;       /* number of relocation entries */
    uint32_t        flags;        /* flags (section type and attributes)*/
    uint32_t        reserved1;    /* reserved (for offset or index) */
    uint32_t        reserved2;    /* reserved (for count or sizeof) */
};

struct				s_mach_sect_64
{                   /* struct section_64 for 64-bit */
    char            sectname[16]; /* name of this section */
    char            segname[16];  /* segment this section goes in */
 	uint64_t        addr;         /* for memory address of this section *///exist que pour 64
	uint64_t        size;         /* for size in bytes of this section */ //exist que pour 64
    uint32_t        offset;       /* file offset of this section */
    uint32_t        align;        /* section alignment (power of 2) */
    uint32_t        reloff;       /* file offset of relocation entries */
    uint32_t        nreloc;       /* number of relocation entries */
    uint32_t        flags;        /* flags (section type and attributes)*/
    uint32_t        reserved1;    /* reserved (for offset or index) */
    uint32_t        reserved2;    /* reserved (for count or sizeof) */
	uint32_t        reserved3;    /* reserved */							//exist que pour 64
};

struct 				s_fat_head
{
	uint32_t		magic;      /* FAT_MAGIC or FAT_MAGIC_64 */
    uint32_t		nfat_arch;  /* number of structs that follow */
};

struct 				s_fat_arch_32	/* struct fat_arch_64 for 64-bit*/
{
	int				cputype;    /* cpu specifier (int) */
	int				cpusubtype; /* machine specifier (int) */
	uint32_t        offset;     /* file offset to this object file *///exist que pour 32
	uint32_t        size;       /* size of this object file */		//exist que pour 32
    uint32_t        align;      /* alignment as a power of 2 */
};


struct 				s_fat_arch_64	/* struct fat_arch_64 for 64-bit*/
{
	int				cputype;    /* cpu specifier (int) */
	int				cpusubtype; /* machine specifier (int) */
	uint64_t        offset;     /* file offset to this object file */	//exist que pour 64
	uint64_t        size;       /* size of this object file */			//exist que pour 64
    uint32_t        align;      /* alignment as a power of 2 */
	uint32_t        reserved;   /* reserved */ 							//exist que pour 64
};



#endif
