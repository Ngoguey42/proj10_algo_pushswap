/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 09:46:47 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/02 14:39:38 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ps.h>

#define TENTH_1 (nb <= (num_vals * 1) / 10)
#define TENTH_2 (nb <= (num_vals * 2) / 10)
#define TENTH_3 (nb <= (num_vals * 3) / 10)
#define TENTH_4 (nb <= (num_vals * 4) / 10)
#define TENTH_5 (nb <= (num_vals * 5) / 10)
#define TENTH_6 (nb <= (num_vals * 6) / 10)
#define TENTH_7 (nb <= (num_vals * 7) / 10)
#define TENTH_8 (nb <= (num_vals * 8) / 10)
#define TENTH_9 (nb <= (num_vals * 8) / 10)

static void	tenth(DBUFF_T nb, DBUFF_T num_vals, char buf[16])
{
	if (TENTH_1)
		ft_strcpy(buf, ":cya::dar:");
	else if (TENTH_2)
		ft_strcpy(buf, ":cya:");
	else if (TENTH_3)
		ft_strcpy(buf, ":cya::lig:");
	else if (TENTH_4)
		ft_strcpy(buf, ":gre::lig:");
	else if (TENTH_5)
		ft_strcpy(buf, ":gre:");
	else if (TENTH_6)
		ft_strcpy(buf, ":gre:");
	else if (TENTH_7)
		ft_strcpy(buf, ":gre::dar:");
	else if (TENTH_8)
		ft_strcpy(buf, ":red::lig:");
	else if (TENTH_9)
		ft_strcpy(buf, ":red:");
	else
		ft_strcpy(buf, ":red::dar:");
	return ;
}

void		ps_get_nb_grad(DBUFF_T nb, DBUFF_T init, char buf[16])
{
	static DBUFF_T	num_vals;

	if (init != 0)
	{
		num_vals = init;
		return ;
	}
	*buf = '\0';
	if (nb == 0)
		ft_strcpy(buf, ":yel:");
	else if (nb == 1)
		ft_strcpy(buf, ":cya::dar::und:");
	else if (nb == num_vals)
		ft_strcpy(buf, ":red::dar::und:");
	else
		tenth(nb, num_vals, buf);
	return ;
}

void		ps_print_dbuff_content(const t_dbuff *dbuff)
{
	int		i;
	char	buf[16];

	i = 0;
	ft_dprintf(2, ":yel:");
	while (i < (int)dbuff->buf_size)
	{
		ps_get_nb_grad(dbuff->buf_rear[i], 0, buf);
		ft_dprintf(2, "%s%hu\033[0m", buf, dbuff->buf_rear[i]);
		i++;
	}
	ft_dprintf(2, ":eof:\n");
	return ;
}

void		ps_print_dbuff(const t_dbuff *dbuff)
{
	ft_dprintf(2, "Dynamic buffer:\n");
	ft_dprintf(2, "buff : rear{%16p} front{%16p} size(%u)\n",
		dbuff->buf_rear, dbuff->buf_front, dbuff->buf_size);
	ft_dprintf(2, "zone : rear{%16p} front{%16p} size(%u)\n",
		dbuff->zone_rear, dbuff->zone_front, dbuff->zone_size);
	if (dbuff->zone_size != 0)
		ft_dprintf(2, "delta: rear{%16u} front{%16u} size(%u)\n",
			dbuff->zone_rear - dbuff->buf_rear,
			dbuff->buf_front - dbuff->zone_front,
			dbuff->buf_size - dbuff->zone_size);
	ps_print_dbuff_content(dbuff);
	return ;
}
