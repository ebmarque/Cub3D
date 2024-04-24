/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:50:40 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/24 20:55:21 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <math.h>
# include <time.h>
# include <stdarg.h>

int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
int			ft_is_space(char c);
int			ft_count_words(char *str, char *sep);
int			ft_word_length(char *str, char *sep);
char		*ft_strndup(const char *s, size_t n);
char		**ft_split(char *str, char *sep);
void		ft_free_split(char **array, int position, bool full);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strchr(char *buffer, int target);
char		*ft_strdup(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strjoin(char *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strncpy(char *dest, const char *src, size_t n);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//GET_NEXT_LINE
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char		*ft_get_line(char *aux);
char		*ft_new_aux(char *aux);
char		*get_next_line(int fd);
char		*ft_read_to_aux(int fd, char *str);

//PRINTF

typedef struct stct_print
{
	va_list	args;
	int		hstg;
	int		zero;
	int		dash;
	int		space;
	int		plus;
	int		dot;
	int		tlen;
	int		error;
}	t_print;

int			ft_check_specifier(t_print *tab, const char *format, int i);
int			ft_print_char(t_print *tab);
int			ft_print_int(t_print *tab);
int			ft_print_lowhex(t_print *tab);
int			ft_print_mem(t_print *tab);
int			ft_print_percent(void);
int			ft_print_str(t_print *tab);
int			ft_print_upperhex(t_print *tab);
int			ft_print_usgdec(t_print *tab);
int			ft_printf(const char *format, ...);
void		ft_init_tab(t_print *tab);
int			ft_is_flag(char c);
int			ft_action_sign(t_print *tab, const char *format, int i);

#endif