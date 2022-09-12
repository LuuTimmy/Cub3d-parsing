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