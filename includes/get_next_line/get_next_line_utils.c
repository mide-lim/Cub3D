/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mide-lim <mide-lim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:44:16 by mide-lim          #+#    #+#             */
/*   Updated: 2024/12/22 16:31:25 by mide-lim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

char	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	const char	*s;
	size_t		i;

	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*strdup;

	len = ft_strlen(s);
	strdup = (char *)malloc((len + 1) * sizeof(char));
	if (!strdup)
		return (NULL);
	strdup = ft_memcpy(strdup, s, len);
	strdup[len] = '\0';
	return (strdup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*sjoin;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	sjoin = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!sjoin)
		return (NULL);
	ft_memcpy(sjoin, s1, l1);
	ft_memcpy(sjoin + l1, s2, l2);
	sjoin[l1 + l2] = '\0';
	return (sjoin);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substring;
	size_t	len_s;
	size_t	len_substring;

	if(!s)
		return (NULL);
	len_s = ft_strlen(s);
	len_substring = len_s - start;
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > len_substring)
		len = len_substring;
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	ft_memcpy(substring, (s + start), len);
	substring[len] = '\0';
	return (substring);
}
// MAIN TESTER FUNCTIONS UTILITS
/*
int	 main(void)
{
	char	dest[20] = {0};
	char	src[25] = "Copy this txt !";

	printf("\v\tSTRLEN TESTER\n");
	printf("This is strlen of Hello: %ld\n", ft_strlen("Hello"));
	printf("This is strlen of void string: %ld\n", ft_strlen(""));
	printf("This is strlen of 42: %ld\n", ft_strlen("42"));
	printf("This is strlen of src: %ld\n", ft_strlen(src));

	printf("\v\tMEMCPY TESTER\n");
	printf("This is dest comming form src, '%s' : '%s'\n",
			src, ft_memcpy(dest, src, ft_strlen(src)));

	printf("\v\tSTRDUP TESTER\n");
	char *dup = ft_strdup("duplicate me !");
	printf("Duplicated string: '%s'\n", dup);
	free(dup);
	dup = ft_strdup("");
	printf("Duplicated empty string: '%s'\n\n", dup);
	free(dup);

	printf("\v\tSTRJOIN TESTER\n");
	char *joined = ft_strjoin("Hello, ", "World!");
	printf("Joined string: '%s'\n", joined);
	free(joined);
	joined = ft_strjoin("", "World !");
	printf("Joined with empty string: '%s'\n\n", joined);
	free(joined);

	printf("\v\tSUBSTR TESTER\n");
	char *sub = ft_substr("This is substring test.", 5, 10);
	printf("Substring: '%s'\n", sub);
	free(sub);
	sub = ft_substr("Short string", 15, 5);
	printf("Substring with start > len: '%s'\n", sub);
	free(sub);
	sub = ft_substr("Substring", 3, 50);
	printf("Substring with len > rest: '%s'\n", sub);
	free(sub);
	return (0);
}*/
