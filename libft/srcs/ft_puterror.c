/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 00:47:08 by ashih             #+#    #+#             */
/*   Updated: 2018/04/09 01:51:35 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_puterror(char *message, char *term, int ret)
{
	if (term)
		ft_printf("{poop} Error: %s: {red}%s{reset}\n", message, term);
	else
		ft_printf("{poop} Error: %s\n", message);
	return (ret);
}
