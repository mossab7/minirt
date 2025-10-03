/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:31:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/10/01 18:11:04 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <sys/wait.h>
# include <colors.h>
# include <fcntl.h>
# include <container.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>
# include <math.h>

# define CHILD_PROC 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define SUCCESS 0
# define CMD_NOT_FOUND 127
# define NON_EXEC 126
# define ERROR -1
# define FAILIURE 1
# define FALSE 0
# define TRUE 1
# define N_TMP 16
# define TMP_SIZE 64

typedef struct s_list
{
	void			*content;
	size_t			index;
	struct s_list	*next;
}					t_list;

typedef struct s_darr
{
	void	**items;
	size_t	capacity;
	size_t	size;
}	t_darr;

typedef struct s_ternary
{
	bool	condition;
	void	*if_true;
	void	*if_false;
	size_t	size;
	void	*dest;
}	t_ternary;

void				darr_init(t_darr *arr);
void				darr_push(t_darr *arr, void *item);
void				darr_free_arr(t_darr *arr, void (*f)(void *));
int					ft_atoi(const char *nptr);
long				ft_atol(const char *nptr);
double				ft_atof(char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isblank(int c);
int					ft_isspace(int c);
bool				ft_isdir(const char *filename);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t dsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_strlen_until(const char *str, char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_strisempty(char *str);
int					ft_strisdecimal(char *str);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_itoa(int n);
int					ft_strisnum(const char *str);
char				*ft_strndup(const char *src, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(const char *s, char c);
char				*ft_strtrim(const char *s, const char *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_putchar_fd(char c, int fd);
int					ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(int n, int fd);
int					ft_putstr_fd(char *s, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstassign_index(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstpush(t_list **from, t_list **to);
void				ft_lstreverse_rotate(t_list **head);
void				ft_lstrotate(t_list **head);
void				ft_lstswap(t_list **head);
void				ft_lstprint(t_list *lst, void (*print_content)(void *));
int					ft_printf(const char *fmt, ...);
int					ft_dprintf(int fd, const char *fmt, ...);
int					ft_snprintf(char *str, size_t size, const char *fmt, ...);
int					ft_execvpe(char *file, char **av, char **envp);
char				**ft_tokenize(char const *s);
char				*ft_getenv(char **envp, char *var);
char				**ft_getpath(char *path);
void				**ft_free_vector(char **vector);

void				*tmp(void *value, size_t size);
void				ternary_(t_ternary t);
void				*ternary(int condition, void *a, void *b);

char				*ft_getoutput(char **argv, char **envp);

typedef struct s_alloc_record
{
	void					*resource;
	void					(*free_func)(void *);
	struct s_alloc_record	*next;
}							t_alloc_record;

void				*alloc(size_t cap);
void				ft_free(void *addr);
void				free_resource(void (*free_func)(void *), void *resource);
void				cleanup_memory_tracker(t_alloc_record **memory_records);
void				detach_resource(t_alloc_record **memory_records,
						void *target_resource);
int					ft_open(const char *filename, int flags);
void				ft_close(void *fd);
t_alloc_record		**get_memory_tracker(void);
void				handle_allocation_failure(void *resource);
void				*allocate_tracked_memory(size_t size);
t_alloc_record		*create_memory_record(void *resource,
						void (*deallocator)(void *));
void				register_memory_allocation(t_alloc_record **memory_records,
						t_alloc_record *new_record);
#endif // !LIBFT_H
