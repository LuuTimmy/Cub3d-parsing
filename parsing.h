#ifndef PARSING_H
#define PARSING_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *str);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	free_split(char **fstr);
int		nword(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int     verifset(char c, const char *set);

#endif