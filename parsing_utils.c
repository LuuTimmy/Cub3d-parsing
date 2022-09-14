#include "parsing.h"

size_t	ft_strlen(const char *str)
{
	size_t  i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*c;
	int		i;

	i = 0;
	while (src[i] != '\0')
		i++;
	c = (char *)malloc(sizeof (char) * (i + 1));
	if (c == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		c[i] = src[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

int	verifset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == '\0')
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}





int	nword(char const *s, char c)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	while (s[i])
	{
		if (s[i + 1] == '\0')
		{
			if (s[i] != c)
				nbword++;
			return (nbword);
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			nbword++;
		i++;
	}
	return (nbword);
}

void	free_split(char **fstr)
{
	int	i;

	i = 0;
	while (fstr[i])
	{
		free(fstr[i]);
		i++;
	}
	free(fstr);
}

static char	**putword(char **fstr, const char *s, char c)
{
	int		nword;
	size_t	len;
	int		i;

	nword = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			len = 0;
			while (s[i + len] != c && s[i + len] != '\0')
				len++;
			fstr[nword] = ft_substr(s, i, len);
			if (!fstr[nword])
				free_split(fstr);
			i += len;
			nword++;
		}
	}
	return (fstr);
}

char	**ft_split(char const *s, char c)
{
	char	**fstr;
	int		nbword;

	if (s == NULL)
		return (NULL);
	nbword = nword(s, c);
	fstr = (char **) malloc (sizeof (char *) * (nbword + 1));
	if (!fstr)
		return (NULL);
	fstr[nbword] = 0;
	putword(fstr, s, c);
	return (fstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*fstr;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	fstr = (char *) malloc (sizeof(char) * (len + 1));
	if (!fstr)
		return (NULL);
	while (*s1)
	{
		fstr[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		fstr[i] = *s2;
		i++;
		s2++;
	}
	fstr[i] = '\0';
	return (fstr);
}
