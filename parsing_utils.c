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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = (char *) malloc (sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	verifset(char c, const char *set)
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

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		nset;
	int		nsetend;
	char	*fdest;
	int		j;

	nset = 0;
	nsetend = 0;
	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	while (verifset(s1[i++], set) == 1)
		nset++;
	i = ft_strlen(s1);
	while ((int)ft_strlen(s1) > nset && verifset(s1[--i], set) == 1)
		nsetend++;
	fdest = ft_substr(s1, nset, (ft_strlen(s1) - nset - nsetend));
	return (fdest);
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