/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_struct_ps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 14:01:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/23 14:38:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ps.h"

static void		check_the_nb(char *str)
{
	int		len;
	int		is_neg;

	len = 0;
	is_neg = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_neg++;
		str++;
	}
	while (*str == '0')
		str++;
	while (str[len] != '\0')
	{
		if (!ft_isdigit(str[len]) || len > 10)
			ft_exit("Error");
		len++;
	}
	if (len > 10 || (is_neg == 0 && len == 10 &&
	ft_strcmp(str, "2147483647") > 0) || (is_neg == 1 && len == 10 &&
	ft_strcmp(str, "2147483648") > 0))
		ft_exit("Error");
}

static void		check_and_put_savereal(int *ac, char **av, t_corresp *corresp)
{
	int		i;

	if (*ac == 0)
		ft_exit("Error");
	corresp->ref = (int*)malloc(sizeof(int) * (*ac + 1));
		if (!corresp->ref)
		ft_exit("Error");
	corresp->ref[*ac] = 0;
	i = 1;
	while (i <= *ac)
	{
		check_the_nb(av[i]);
		corresp->ref[*ac - i + 1] = ft_atoi(av[i]);
		/* corresp->ref[i - 1] = ft_atoi(av[i]); */
		D(int, i);
		D(int, corresp->ref[*ac - i + 1]);
		i++;
	}
}

void			put_struct_ps(int *ac, char **av, t_corresp *corresp)
{
	*ac = *ac - 1;
	check_and_put_savereal(ac, av, corresp);
	put_a_b_solved(corresp, *ac);
}
