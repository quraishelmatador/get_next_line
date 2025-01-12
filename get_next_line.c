/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktayabal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:02:52 by ktayabal          #+#    #+#             */
/*   Updated: 2025/01/04 19:02:54 by ktayabal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"	

static char	*read_and_stash(int fd, char *buf, char *backup)
{
	int		bytes_read;
	char	*char_temp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		else if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		if (!backup)
			backup = ft_strdup("");
		char_temp = backup;
		backup = ft_strjoin(char_temp, buf);
		free(char_temp);
		char_temp = NULL;
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract(char *line)
{
	size_t	nl_index;
	char	*backup;

	nl_index = 0;
	while (line[nl_index] != '\n' && line[nl_index] != '\0')
		nl_index++;
	if (line[nl_index] == '\0' || line[1] == '\0')
		return (0);
	backup = ft_substr(line, nl_index + 1, ft_strlen(line) - nl_index);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[nl_index + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = read_and_stash(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	backup = extract(line);
	return (line);
}
