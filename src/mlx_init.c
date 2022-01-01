/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 00:24:30 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/01 17:43:50 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	framebuffer_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

static bool	mlx_init_frame(t_MLX *mlx)
{
	float	vertices[] = {
		// positions         // colors
		1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	mlx->vao = VAO;
	return (true);
}

static bool	mlx_init_render(t_MLX *mlx)
{
	uint32_t	s[3];

	if (!mlx->window)
		return (mlx_error(GLFW_WIN_FAILURE));
	glfwMakeContextCurrent(mlx->window);
	glfwSetFramebufferSizeCallback(mlx->window, framebuffer_callback);
	glfwSwapInterval(true);
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			return (mlx_error(GLFW_GLAD_FAILURE));
		if (!mlx_compile_shader(VERTEX_PATH, GL_VERTEX_SHADER, &s[0]) || \
			!mlx_compile_shader(FRAGMENT_PATH, GL_FRAGMENT_SHADER, &s[1]))
			return (mlx_error(MLX_SHADER_FAILURE));
	}
	s[2] = 0;
	if (!mlx_init_shaders(mlx, s))
		return (mlx_error(MLX_SHADER_FAILURE));
	glDeleteShader(s[0]);
	glDeleteShader(s[1]);
	glUseProgram(mlx->shaderprogram);
	return (mlx_init_frame(mlx));
}

t_MLX	*mlx_init(int32_t Width, int32_t Height, const char *Title, bool Resize)
{
	t_MLX		*mlx;
	const bool	init = glfwInit();

	mlx = calloc(1, sizeof(t_MLX));
	if (!mlx || !init)
	{
		free(mlx);
		return ((void *)mlx_error(GLFW_INIT_FAILURE));
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (IS_APPLE)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, Resize);
	mlx->width = Width;
	mlx->height = Height;
	mlx->window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
	if (!mlx_init_render(mlx))
	{
		free(mlx);
		return ((void *)mlx_error(MLX_RENDER_FAILURE));
	}
	return (mlx);
}