/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:52 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/23 19:34:01 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
#define CORE_H

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"

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


typedef struct s_cub
{
	char *map_name;
	char **map_content;	
}				t_cub;


/*---------------------------------- ERROR -----------------------------------*/

void	_check_erros(int argc, char **argv);
void	_check_file_name(char *file);
void	_check_file_permissions(char *file);


# define WIDTH 1200
# define HEIGHT 840

#endif