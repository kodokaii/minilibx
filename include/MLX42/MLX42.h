/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 00:33:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/03 16:23:00 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * OpenGL graphics library based on the idea on what MiniLibX
 * provides. Just quite a bit better, in terms of norme and code quality.
 * 
 * Additionally with glfw its cross-platform, unlike before.
 * 
 * As for the few void* present in some structs and why MLX is split into
 * two different headers, so to speak, is mainly for abstraction. Most users
 * won't have a need for the inner workings of MLX (shaders, ...) and it also
 * helps keep MLX nice and tidy.
 * 
 * @note Useful stuff for later:
 * https://bit.ly/3qQof6q
 * __attribute__ ((deprecated));
 * 
 * Written in accordance with norminette 3.3.51.
 */

#ifndef MLX42_H
# define MLX42_H
# include <stdint.h>
# include <stdbool.h>
# include "MLX42_Keys.h"
# include "MLX42_Vec.h"

/**
 * Main MLX handle, carries important data in regard to the program.
 * TODO: Abstract VAO and Shaderprogram.
 * @param window The window itself.
 * @param hooks List of all the current hooks.
 * @param title The title of the window.
 * @param width The width.
 * @param height The height.
 */
typedef struct s_MLX
{
	void		*window;
	void		*hooks;
	int32_t		width;
	int32_t		height;
	uint32_t	shaderprogram;
	uint32_t	vao;
}	t_MLX;

/**
 * Main MLX handle, carries important data in regard to the program.
 * @param width The width of the canvas.
 * @param height The height of the canvas.
 * @param pixels The literal pixel data.
 * @param context Additional internal image context used by MLX.
 */
typedef struct s_mlx_canvas
{
	int32_t	width;
	int32_t	height;
	int32_t	*pixels;
	void	*context;
}	t_mlx_canvas;

/**
 * Initilizes a new MLX42 Instance.
 * 
 * @param Width The width of the window.
 * @param Height The height of the window.
 * @param Title The title of the window.
 * @return Ptr to the MLX handle.
 */
t_MLX	*mlx_init(int32_t Width, int32_t Height, const char *Title, \
bool Resize);

/**
 * Adds a function hook to the main loop. Aka, executes a function per frame.
 * 
 * @param mlx The MLX instance handle.
 * @param f The function.
 * @param param The parameter to pass onto the function.
 * @return Wether the hook was added successfuly. 
 */
bool	mlx_loop_hook(t_MLX *mlx, void (*f)(void *), void *param);

/**
 * Terminates MLX and cleans up any of its used resources.
 * 
 * @param mlx The MLX instance handle.
 */
void	mlx_terminate(t_MLX *mlx);

// TODO: Remove and replace with putpixel_canvas instead...
void	mlx_putpixel(t_MLX *MLX, int32_t X, int32_t Y, int32_t Color);

/**
 * Returns true or false if the key is down or not.
 * 
 * @param mlx The MLX instance handle.
 * @param key The keycode to check, use MLX_KEY_... to specify!
 * @return True or false if the key is down or not.
 */
bool	mlx_is_key_down(t_MLX *mlx, t_keys key);

/**
 * Returns the current, relative, mouse cursor position on the window, starting
 * from the top left corner.
 * 
 * Negative values or values greater than window width or height 
 * indicate that it is outside the window.
 * 
 * @param mlx The MLX instance handle. 
 * @param pos_out The position.
 */
void	mlx_get_mouse_pos(t_MLX *mlx, t_IVec2 *pos_out);

/**
 * Tells MLX that it should stop rendering and quit the main loop.
 * Make sure to call terminate after calling this function.
 * 
 * @param mlx The MLX instance handle.
 */
void	mlx_quit(t_MLX *mlx);

/**
 * The program loop, this will cause MLX to continously render
 * and output its content. Can be halted with mlx_quit.
 * 
 * @param mlx The MLX instance handle.
 */
void	mlx_loop(t_MLX *mlx);

#endif