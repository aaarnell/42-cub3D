/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:10:18 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/09 18:50:48 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUF_GETNEXTLINE
#  define BUF_GETNEXTLINE 32
# endif

# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Работа со строками и массивами
void	*ft_memset(void *dst, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *str, int ch);
char	*ft_strrchr(const char *str, int ch);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_atoi(const char *str);

// Работа с двумерными массивами
size_t	ft_arrlen(void **arr);
int		ft_search_str_in_arr(char **arr, char *str);
size_t	ft_str_in_arrstr(char **arr, char *str, size_t len_s);

// Работа с символами ASCII
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

// Работа со строками с выделением памяти
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_get_next_line(int fd, char **line);

// Работа с двумерными массивами c выделением памяти
char	**ft_arrcpy_strdup(char **from, char **to);
char	**ft_subarr_strdup(char **from, char **to, int start, size_t len);
char	**ft_add_str_to_arr(char **arr, char *str);
char	**ft_del_str_from_arr(char **arr, char *str);
int		ft_frmtrx(char **str);

// Вывод символов и строк
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Работа со односвязными списками
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));



#endif
