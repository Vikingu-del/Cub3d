/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:28:20 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/16 10:18:30 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	void	*calloc_result;

	if (ptr == NULL)
	{
		calloc_result = ft_calloc(size, 1);
		if (!calloc_result)
			return (NULL);
		else
			return (calloc_result);
	}
	if (!size)
		return (ptr);
	new_ptr = ft_calloc(size, 1);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*trim_whitespace(const char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(strlen(str) + 1);
	if (result == NULL)
		exit_program(NULL, 1, MALLOC_ERROR);
	while (ft_isspace((unsigned char)str[i]))
		i++;
	while (str[i] != '\0')
	{
		if (ft_isspace((unsigned char)str[i]))
		{
			while (ft_isspace((unsigned char)str[i]))
				i++;
			if (str[i] != '\0')
				result[j++] = ' ';
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*custom_strdup(const char *src)
{
	char	*dest;
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(src) + 1;
	dest = (char *)malloc(sizeof(char) * i);
	if (dest == NULL)
		return (0);
	while (j < i)
	{
		if (src[j] == '\n' || src[j] == '\0')
		{
			dest[j] = '\0';
			break ;
		}
		dest[j] = src[j];
		j++;
	}
	return (dest);
}
