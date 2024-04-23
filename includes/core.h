/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:52 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/23 19:52:14 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include "../src/LIB/LIBFT/libft.h"

# ifdef __APPLE__

#  include "../src/LIB/MLX_MAC/mlx.h"

# elif defined(__linux__)

#  include "../src/LIB/MLX_LINUX/mlx.h"

# endif

# ifdef __APPLE__

typedef enum e_key
{
	ESC = 53,
	A = 0,
	S = 1,
	D = 2,
	W = 13,
	Q = 12,
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123
}		t_key;

typedef enum e_mask
{
	KEY_MASK = 0,
	CLOSE_MASK = 0
}	t_mask;

# elif defined(__linux__)

typedef enum e_key
{
	ESC = 65307,
	A = 97,
	S = 115,
	D = 100,
	W = 119,
	Q = 113,
	UP = 65362,
	DOWN = 65364,
	RIGHT = 65363,
	LEFT = 65361
}		t_key;

typedef enum e_mask
{
	KEY_MASK = (1L << 0),
	CLOSE_MASK = (1L << 17)
}	t_mask;

# endif

typedef struct s_cub
{
	char	*map_name;
	char	**map_content;	
}				t_cub;

/*---------------------------------- ERROR -----------------------------------*/

void	_check_erros(int argc, char **argv);
void	_check_file_name(char *file);
void	_check_file_permissions(char *file);
void	_check_empty_file(char *file);

# define WIDTH 1200
# define HEIGHT 840

#endif