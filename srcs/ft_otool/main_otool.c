/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_otool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:21:19 by pbernier          #+#    #+#             */
/*   Updated: 2019/08/29 16:21:20 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <ft_otool.h>

int		main(int argc, char **argv)
{
	t_flags	flags;
	int		files;

	if ((files = check_usage(argc, argv, &flags)) == RETURN_FAIL)
		return (RETURN_FAIL);
	while (argv[files] && !open_file(argv[files], &flags))
		++files;
	return (RETURN_SUCESS);
}

int		check_usage(int argc, char **argv, t_flags *flags)
{
	int		len;

	ERROR_INIT(NULL);
	if (argc < 2)
		return (error_usage());
	len = 1;
	while (len < argc && argv[len][0] == '-')
	{
		if (check_flags(argv[len], (char *)flags))
			return (error_usage());
		++len;
	}
	if (!argv[len])
		return (error_otool(ERROR_USAGE_NO_FILE));
	if (len == 1)
		flags->text_section = true;
	return (len);
}

int		check_flags(char *argv, char *flags)
{
	size_t	len[3];

	if ((SIZE_ARGV = len_text(argv)) == 1)
		return (error_otool(ERROR_USAGE_FLAG));
	LEN_ARGV = 1;
	while (LEN_ARGV < SIZE_ARGV)
	{
		LEN_FLAGS = 0;
		while (LEN_FLAGS < NUMBER_FLAGS
			&& (CHAR_FLAGS)[LEN_FLAGS] != argv[LEN_ARGV])
			++LEN_FLAGS;
		if (LEN_FLAGS == NUMBER_FLAGS)
		{
			error_otool(ERROR_USAGE_UNKNOWN_CHAR);
			error_e_un_c(argv[LEN_ARGV], argv);
		 	return (RETURN_FAIL);
		}
		if (!flags[LEN_FLAGS])
			flags[LEN_FLAGS] = 1;
		++LEN_ARGV;
	}
	return (RETURN_SUCESS);
}