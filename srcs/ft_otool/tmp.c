
# define BUFF_HEADER	((t_header*)(&buff[0]))
# define BUFF_SEGMENT	((t_segment*)(&buff[0]))
# define HEAD_START		octect[0]
# define HEAD_END		octect[1]

void		read_header(int fd)
{
	unsigned int	octect[2];
	char			buff[128];

	HEAD_START = read(fd, buff, 32);
	HEAD_END = BUFF_HEADER->sizeofcmds;
	//print_header(*BUFF_HEADER);

	while (HEAD_START < HEAD_END)
	{
		HEAD_START += read(fd, buff, 64);
		//check_segname(BUFF_SEGMENT->segname, "__text");
		//print_segment(*BUFF_SEGMENT);
	}
}

void		read_data(int fd)
{
	int				len;
	unsigned char	buff[SIZE_BUFF];
	long long		count;

	count = 0;
	while ((len = read(fd, buff, SIZE_BUFF)) > 0)
	{
		//print_count(count);
		count += 16;
		//print_data(buff, len);
	}
}


void 		print_header(t_header header)
{
	printf("magic\t\t= [%u]\ncputype\t\t= [%i]\ncpusubtype\t= [%i]\nfiletype\t= [%u]\nncmds\t\t= [%u]\nsizeofcmds\t= [%u]\nflags\t\t= [%u]\n\n",
			header.magic, header.cputype, header.cpusubtype, header.filetype, header.ncmds, header.sizeofcmds, header.flags);
}

void 		print_segment(t_segment segment)
{
	printf("cmd\t\t= [%u]\ncmdsize\t\t= [%u]\nsegname\t\t= [%s]\nvmaddr\t\t= [%u]\n"
	"vmsize\t\t= [%u]\nfileoff\t\t= [%u]\nfilesize\t= [%u]\nmaxprot\t\t= [%i]\n"
	"initprot\t= [%i]\nnsects\t\t= [%u]\nflags\t\t= [%u]\n\n",
			segment.cmd, segment.cmdsize, segment.segname, segment.vmaddr,
			segment.vmsize, segment.fileoff, segment.filesize, segment.maxprot,
			segment.initprot, segment.nsects, segment.flags);
}

// bool		check_segname(char seg_name[16], char check[16])
// {
// 	short	i;
//
// 	i = 0;
// 	while (seg_name[i] == check[i] && check[i] && i < 16)
// 		++i;
// 	return ((i == 16 || !check[i]) ? true : false);
// }

// void	tmp(int fd, int len, unsigned char buff[BUFF], long long count)
// {
// 	t_header	tmp[1];
// 	int			q = 0;
// 	t_segment	seg[1];
// 	//read(fd, buff, sizeof(t_header));
// 	read(fd, tmp, 32);
//
//
// 	while (q++ < 8)
// 	{
// 		read(fd, seg, 64);
// 		printf("%d\n", q);
// 		printf("cmd\t\t= [%u]\ncmdsize\t\t= [%u]\nsegname\t\t= [%s]\nvmaddr\t\t= [%u]\n"
// 		"vmsize\t\t= [%u]\nfileoff\t\t= [%u]\nfilesize\t= [%u]\nmaxprot\t\t= [%i]\n"
// 		"initprot\t= [%i]\nnsects\t\t= [%u]\nflags\t\t= [%u]\n\n",
// 		segment.cmd, segment.cmdsize, segment.segname, segment.vmaddr,
// 		segment.vmsize, segment.fileoff, segment.filesize, segment.maxprot,
// 		segment.initprot, segment.nsects, segment.flags);
// 	//	segment = ((t_segment){0, 0, 0, 0, 0, 0, 0, 0, 0});
// 	}
// 	(void)fd;
// 	(void)len;
// 	(void)buff;
// 	(void)count;
// }
