/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:17:10 by pbernier          #+#    #+#             */
/*   Updated: 2019/09/30 19:17:11 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int		read_fat(void *data, bool endian, t_eflags flag)
{
	uint32_t		count_arch;

	count_arch = ((t_ft_head*)data)->nfat_arch;
	// printf("[%u]\n", ((t_ft_head*)data)->magic);
	// printf("[%u]\n", ((t_ft_head*)data)->nfat_arch);
	//while (count_arch++ < ((t_ft_head*)data)->nfat_arch )
	// {
	// 	printf("hh\n");
	// }
	// printf("[%u]\n[%u]\n",
	// ((t_ft_arch_64*)(data + sizeof(t_ft_head)))->cputype,
	// ((t_ft_arch_64*)(data + sizeof(t_ft_head)))->cpusubtype);

	data += sizeof(t_ft_head*);
	while (count_arch--)
	{
		//printf("[%llu]\n", ((t_ft_arch_64*)(data))->offset);
		if (((t_ft_arch_32*)(data))->offset == MH_CIGAM_64 ||
			((t_ft_arch_32*)(data))->offset == MH_MAGIC_64 ||
			((t_ft_arch_32*)(data))->offset == MH_MAGIC ||
			((t_ft_arch_32*)(data))->offset == MH_CIGAM)
			{
				data = &((t_ft_arch_32*)(data))->offset;
				printf("[%u]\n", ((t_ft_head*)data)->magic);
				printf("[%u]\n", ((t_ft_head*)data)->nfat_arch);
				return (RETURN_SUCESS);
			}
		else
			printf(".");
		data += sizeof(t_ft_arch_32*);
	}

	(void)data;
	(void)endian;
	(void)flag;
	printf("OUEXH\n");
	return (RETURN_SUCESS);
}
