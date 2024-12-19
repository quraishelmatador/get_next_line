/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktayabal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:25:31 by ktayabal          #+#    #+#             */
/*   Updated: 2024/12/15 15:25:32 by ktayabal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_new_stash(char *stash, int i)
{
	int		j;
	char	*new_stash;

	new_stash = malloc(ft_strlen(stash) - i);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	return (new_stash);
}

static char	*update_stash(char *stash)
{
	int		i;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	return (get_new_stash(stash, i));
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			break ;
	}
	free(buffer);
	return (stash);
}

static char	*get_line_and_update_stash(char **stash)
{
	char	*line;

	if (!*stash || !**stash)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	line = extract_line(*stash);
	*stash = update_stash(*stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	return (get_line_and_update_stash(&stash));
}

/*// Function to extract the line from stash
static char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash || !*stash) // Safety check for NULL or empty stash
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

// Function to update the stash after extracting the line
static char	*update_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = 0;
	if (!stash || !*stash) // Safety check for NULL or empty stash
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i]) // No newline found, free stash
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(ft_strlen(stash) - i);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	i++; // Move past the newline character
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}


// Main get_next_line function
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			bytes_read;
	char		*line;

	stash = NULL;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1) // Read error
		{
			free(stash);
			return (NULL);
		}
		if (bytes_read == 0) // End of file
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash) // Check for malloc failure
			return (NULL);
	}
	if (!stash || !*stash) // Handle empty or NULL stash
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
earlier you explained that code to me line by line,
but i dont undertsand how the static variabe works here 
and why should we use one.*/