/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:08:52 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/30 19:08:54 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm_otool.h>

int			check_usage(int argc, char **argv, t_flags *flags)
{
	int			len;
	e_fonction	fonction;

	if (!(fonction = check_fonction(argv[0])) || argc < 2)
		return (error_usage(fonction));
	ERROR_INIT_FONCTION((fonction == ft_nm) ? "ft_nm" : "ft_otool");
	len = 1;
	while (fonction == ft_otool && len < argc && argv[len][0] == '-')
	{
		if (check_flags(argv[len], (char *)flags))
			return (error_usage(fonction));
		//combinaison de flag
		++len;
	}
	if (!argv[len])
		return (error(ERROR_USAGE_NO_FILE));
	if (fonction == ft_otool && len == 1)
		flags->text_section = true;
	else if (fonction == ft_nm)
		flags->symbols_file = true;
	return (len);
}

e_fonction	check_fonction(char *name)
{
	if (name && same_text(name, "./ft_otool"))
		return (ft_otool);
	else if (name && same_text(name, "./ft_nm"))
		return (ft_nm);
	return (ft_null);
}

int		check_flags(char *argv, char *flags)
{
	size_t	len[3];

	if ((SIZE_ARGV = len_text(argv)) == 1)
		return (error(ERROR_USAGE_FLAG));
	LEN_ARGV = 1;
	while (LEN_ARGV < SIZE_ARGV)
	{
		LEN_FLAGS = 0;
		while (LEN_FLAGS < NUMBER_FLAGS
			&& (CHAR_FLAGS)[LEN_FLAGS] != argv[LEN_ARGV])
			++LEN_FLAGS;
		if (LEN_FLAGS == NUMBER_FLAGS)
		{
			error(ERROR_USAGE_UNKNOWN_CHAR);
			error_e_un_c(argv[LEN_ARGV], argv);
		 	return (RETURN_FAIL);
		}
		if (!flags[LEN_FLAGS])
			flags[LEN_FLAGS] = 1;
		++LEN_ARGV;
	}
	return (RETURN_SUCESS);
}
