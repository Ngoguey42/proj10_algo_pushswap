/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 07:55:36 by ngoguey           #+#    #+#             */
/*   Updated: 2015/02/03 10:45:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"

#define DBUFF_FRONT_AFFINITY 2

/*
** 'ft_dbuff_recenter' recenter zone in buffer.
**				'buf_size' - 'zone_size' should never be lower than 4.
**				'zone_size' should never be 0 when resizing.
*/
int			ft_dbuff_init(t_dbuff *dbuff, size_t size)
{
	dbuff->buf_rear = (DBUFF_T*)ft_memalloc(size * sizeof(DBUFF_T));
	if (dbuff->buf_rear == NULL)
		return (ENOMEM);
	dbuff->buf_size = size;
	dbuff->buf_front = dbuff->buf_rear + size;
	dbuff->zone_size = 0;
	dbuff->zone_front = NULL;
	dbuff->zone_rear = NULL;
	return (0);
}

int			ft_dbuff_recenter(t_dbuff *dbuff)
{
	size_t	rear_pad;

	rear_pad = (dbuff->buf_size - dbuff->zone_size) / 2 - DBUFF_FRONT_AFFINITY;
	ft_memmove(dbuff->buf_rear + rear_pad, dbuff->zone_rear, dbuff->zone_size);
	ft_bzero(dbuff->buf_rear, rear_pad);
	dbuff->zone_rear = dbuff->buf_rear + rear_pad;
	dbuff->zone_front = dbuff->zone_rear + dbuff->zone_size;
	ft_bzero(dbuff->zone_front + 1, dbuff->buf_front - dbuff->zone_front);
	return (0);
}
