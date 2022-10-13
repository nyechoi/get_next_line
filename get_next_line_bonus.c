/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nye-eun- <nye-eun-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:51:17 by nye-eun-          #+#    #+#             */
/*   Updated: 2022/10/11 19:29:06 by nye-eun-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_substr(char const *s,
	unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (!s)
	return (NULL);
	size = ft_strlen(s);
	if (start > size)
	{
		len = 1;
		start = 0;
	}
	else if (start + len > size)
	len = size - start + 1;
	else
	len = len + 1;
	sub = malloc(len);
	if (!sub)
	return (NULL);
	ft_strlcpy(sub, s + start, len);
	return (sub);
}

static void	ft_free(char **str)
{
	if (str[0])
	{
		free(str[0]);
		str[0] = NULL;
	}
}

static char	*cut(char **str)
{
	int		i;
	char	*ret;
	char	*aux;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[0][i] != '\n' && str[0][i] != '\0')
		i++;
	ret = ft_substr(str[0], 0, i + 1);
	aux = ft_strdup(str[0]);
	ft_free(str);
	str[0] = ft_substr(aux, i + 1, ft_strlen(aux));
	ft_free(&aux);
	if (!ft_strchr(ret, '\n')) //Não encontra \n no retorno, libera a estática
	{
		if (!ft_strlen(ret)) //Retorno alocado sem conteúdo e não tem nada para retornar
			ft_free(&ret);
		ft_free(str);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	
	char		*buff;
	int			size;
	char		*aux;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	size = read(fd, buff, BUFFER_SIZE);
	while (size > 0)
	{
		buff[size] = '\0';
		if (!str[fd])
			str[fd] = ft_strdup(buff);
		else
		{
			aux = ft_strjoin(str[fd], buff);
			ft_free(&str[fd]);
			str[fd] = aux;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
		size = read(fd, buff, BUFFER_SIZE);
	}
	return (ft_free(&buff), cut(&str[fd]));
}
