/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:21:40 by ljussiau          #+#    #+#             */
/*   Updated: 2023/11/02 10:04:45 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *str)
{
	int		i;
	char	*ret_str;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	ret_str = (char *)malloc(sizeof(char) * (i + 2));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		ret_str[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		ret_str[i] = str[i];
		i++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}

char	*get_new_str(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_str(int fd, char *str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = get_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_get_line(str[fd]);
	str[fd] = get_new_str(str[fd]);
	return (line);
}

int main() {
    int fd1 = open("example.txt", O_RDONLY);
	int fd2 = open("test.txt", O_RDONLY);
    char *str;

	str = get_next_line(-1);
	printf("STR = %s", str);
	free(str);
	str = get_next_line(-1);
	printf("STR = %s", str);
	free(str);
	str = get_next_line(-1);
	printf("STR = %s", str);
	free(str);
	str = get_next_line(fd2);
	printf("STR = %s", str);
	free(str);

	while (1) 
	{
		if (str == NULL)
			break ;
		str = get_next_line(fd1);
		printf("STR = %s", str);
		free(str);
	}
	close(fd1);
	close(fd2);
}

