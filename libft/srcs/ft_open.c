/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:21:00 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 19:06:27 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			init_argv0_path(char *argv0, char **argv0_path)
{
	size_t	len;

	len = ft_strrchr(argv0, '/') - argv0 + 1;
	if (!(*argv0_path = ft_strnew(len)))
		return (ft_puterror(ERROR_MEMORY, 0, 1));
	ft_strncpy(*argv0_path, argv0, len);
	return (0);
}

int			ft_open(char *argv0_path, char *file, int flags)
{
	int		ret;
	char	*filepath;

	if (!(filepath = ft_strjoin(argv0_path, file)))
		return (ft_puterror(ERROR_MEMORY, 0, 1));
	ft_printf("ft_open() : filepath = %s\n", filepath);
	ret = open(filepath, flags);
	ft_strdel(&filepath);
	return (ret);
}
