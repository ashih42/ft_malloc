/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 21:04:30 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 20:21:05 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	VERBOSE_PRINT("ft_calloc ( count=%lu , size=%lu )...\n", count, size);
	ret = ft_malloc(count * size);
	if (ret)
		ft_bzero(ret, count * size);
	VERBOSE_PRINT("ft_calloc ( count=%lu , size=%lu ) : ret\n",
		count, size, ret);
	return (ret);
}
