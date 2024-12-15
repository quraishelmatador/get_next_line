#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

size_t  ft_strlen(const char *s);
void    *ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
char    *ft_strchr(const char *s, int c);
//char *get_next_line(int fd);
char    *ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif
