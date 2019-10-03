/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:06:09 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/30 19:06:10 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm_otool.h>

int		read_match_symtab(t_match match)
{
	uint32_t		count_nlist;
	void*			tab_nlist[SYMTAB->nsyms];

	count_nlist = 0;
	NLIST = match.header + SYMTAB->symoff;
	while (count_nlist++ < SYMTAB->nsyms)
	{
		sort_match_nlist(match, tab_nlist);
		NLIST += sizeof(t_st_nlis_64);
	}
	if (read_match_nlist(match, tab_nlist))
	 	return (RETURN_FAIL);
	return (RETURN_SUCESS);
}

int		sort_match_nlist(t_match match, void **tab_nlist)
{
	static uint32_t	placed = 0;
	uint32_t		len[3];

	LEN_TAB = 0;
	placed += (placed >= SYMTAB->nsyms) ? (-placed) : 1;
	while (LEN_TAB < placed
		&& tab_nlist[LEN_TAB]
		&& sorted_text(STRING(tab_nlist[LEN_TAB]), STRING(NLIST)))
		LEN_TAB++;
	if (tab_nlist[LEN_TAB])
	{
	 	LEN_SAVE = LEN_TAB;
	 	LEN_TAB = placed;
	 	while (LEN_TAB > LEN_SAVE)
	 	{
	 		tab_nlist[LEN_TAB] = tab_nlist[LEN_TAB - 1];
			--LEN_TAB;
		}
	}
	tab_nlist[LEN_TAB] = NLIST;
	return (RETURN_SUCESS);
}

int		read_match_nlist(t_match match, void **tab_nlist)
{
	uint32_t		len;
	unsigned char	bit;
	char			type;

	len = 0;
	while (len < SYMTAB->nsyms)
	{
		bit = (N_TYPE(tab_nlist[len]) & 0x0e);
		if (bit != 0x0 && bit != 0x2)
		 	print_address(N_VALUE(tab_nlist[len]), M_ADDR_SIZE, false);
		else
			write(1, CHAR_SPACE, M_ADDR_SIZE);
		write(1, " ", 1);
		type = '?';
		if (read_match_ntype(match, tab_nlist[len], &type))
			return (-1); //TMP
		write(1, &type, 1);
		write(1, " ", 1);
		write(1, STRING(tab_nlist[len]), len_text(STRING(tab_nlist[len])));
		write(1, "\n", 1);
		len++;
	}
	return (RETURN_SUCESS);
}

int			read_match_ntype(t_match match, void *nlist, char *type)
{
	short			len;
	unsigned char	bit;

	if (N_DESC(nlist))
	{
		*type = 'W';
		return(RETURN_SUCESS);
	}
	if ((bit = (N_TYPE(nlist) & 0xe0)))
		return (RETURN_SUCESS);
	if (!(bit = (N_TYPE(nlist) & 0x0e)))
		*type = N_VALUE(nlist) ? 'c' : 'u';
	len = 0;
	while ((bit) && len < 4)
		if (bit == ((char[4]){0x2, 0xe, 0xc, 0xa})[len++])
			*type = ((char[4]){'a', what_sectname(SECTNAME(nlist)), 'u', 'i'})[len - 1];
	if ((bit = (N_TYPE(nlist) & 0x01)) && *type >= 'a' && *type <= 'z')
	 		*type -= ('a' - 'A');
	return (RETURN_SUCESS);
}

char		what_sectname(char text[16])
{
	short		len;

	len = 0;
	while (len < 3)
		if (same_text(
			(((char*[3]){TEXT_SECT, "__data", "__bss"})[len++]), text))
			return (((char[3]){'t', 'd', 'b'})[len - 1]);
	//error sectname
	return ('s');
}
