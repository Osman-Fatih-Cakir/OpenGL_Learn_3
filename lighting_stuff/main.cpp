
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> // Image loading library for load texture images

#include <shaders.h>

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

// Cube attributes
GLfloat cube_vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
};
GLfloat cube_normals[] = {
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,

	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,
	  0.0f,  0.0f,  1.0f,

	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,
	 -1.0f,  0.0f,  0.0f,

	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,
	  1.0f,  0.0f,  0.0f,

	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,
	  0.0f, -1.0f,  0.0f,

	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f,
	  0.0f,  1.0f,  0.0f
};
GLfloat cube_texture_coord[] = {
	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,

	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,

	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,
	 1.0f,  0.0f,

	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,
	 1.0f,  0.0f,

	 0.0f,  1.0f,
	 1.0f,  1.0f,
	 1.0f,  0.0f,
	 1.0f,  0.0f,
	 0.0f,  0.0f,
	 0.0f,  1.0f,

	 0.0f,  1.0f,
	 1.0f,  1.0f,
	 1.0f,  0.0f,
	 1.0f,  0.0f,
	 0.0f,  0.0f,
	 0.0f,  1.0f
};
std::vector<GLuint> cubeVAOs;
std::vector<mat4> models;

vec3 eye = vec3(0.f, 0.f, 23.f);
vec3 up = vec3(0.f, 1.f, 0.f);
mat4 projection, view;
vec3 light_pos = vec3(11.f, 11.f, 2.f);
vec3 light_ambient = vec3(0.05f, 0.05f, 0.05f);
vec3 light_diffuse = vec3(1.0f, 1.0f, 1.0f);
vec3 light_specular = vec3(1.0f, 1.0f, 1.0f);

float shininess = 16.0f;
float light_constant = 1.0f;
float light_linear = 0.014f;
float light_quadratic = 0.007f;

vec3 light_dir;
float light_cutoff = glm::cos(glm::radians(12.5f));
float light_out_cutoff = glm::cos(glm::radians(17.5f));

int light_mode = 0;

GLuint shader_program;
GLuint view_loc, projection_loc;

GLuint eye_loc, diffuse_loc, specular_loc, shininess_loc;
GLuint light_pos_loc, light_dif_loc, light_amb_loc, light_spe_loc, light_mode_loc;
GLuint light_constant_loc, light_linear_loc, light_quadratic_loc;
GLuint light_dir_loc, light_cutoff_loc, light_out_cutoff_loc;

void init();
void changeViewport(int, int);
void keyboard(unsigned char, int, int);
GLuint load_texture(const char*);
void init_shaders();
void init_light();
void init_cubes();
void draw_cubes();
void init_camera();
void draw_camera();
void draw_light();
void render();

int main(int argc, char* argv[])
{
	// Initialize GLUT
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Create window
	glutCreateWindow("OPENGL APP");
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(800, 800);
	glutReshapeWindow(800, 800);

	// Bind functions
	glutReshapeFunc(changeViewport);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);
	
	// Initialize Glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Unable to initalize Glew ! " << std::endl;
		return 1;
	}

	// Start program
	init();

	glutMainLoop();

	return 0;
}

void changeViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'k':
			light_mode = (light_mode + 1) % 3;
			if (light_mode == 0) std::cout << "Directional light" << std::endl;
			else if (light_mode == 1) std::cout << "Point light" << std::endl;
			else if (light_mode == 2) std::cout << "Spot light" << std::endl;
			break;
		case 'w':
			eye = glm::rotate(mat4(1.f), glm::radians(15.f), vec3(-1.f, 0.f, 0.f)) * vec4(eye, 1.f);
			up = glm::rotate(mat4(1.f), glm::radians(15.f), vec3(-1.f, 0.f, 0.f)) * vec4(up, 1.f);
			view = glm::lookAt(eye, vec3(0.0f, 0.0f, 0.0f), up);
			break;
		case 's':
			eye = glm::rotate(mat4(1.f), glm::radians(15.f), vec3(1.f, 0.f, 0.f)) * vec4(eye, 1.f);
			up = glm::rotate(mat4(1.f), glm::radians(15.f), vec3(1.f, 0.f, 0.f)) * vec4(up, 1.f);
			view = glm::lookAt(eye, vec3(0.0f, 0.0f, 0.0f), up);
			break;
		case 'a':
			eye = glm::rotate(mat4(1.f), glm::radians(15.f), vec3(0.f, -1.f, 0.f)) * vec4(eye, 1.f);
			up = glm::rotate(mat4(1.f), glm::radians(15.f), vec3(0.f, -1.f, 0.f)) * vec4(up, 1.f);
			view = glm::lookAt(eye, vec3(0.0f, 0.0f, 0.0f), up);
			break;
		case 'd':
			eye = glm::rotate(mat4(1.f), glm::radians(15.f), vec3(0.f, 1.f, 0.f)) * vec4(eye, 1.f);
			up = glm::rotate(mat4(1.f), glm::radians(15.f), vec3(0.f, 1.f, 0.f)) * vec4(up, 1.f);
			view = glm::lookAt(eye, vec3(0.0f, 0.0f, 0.0f), up);
			break;
	}
	glutPostRedisplay();
}

GLuint load_texture(const char* path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* image = stbi_load(path, &width, &height, &nrComponents, 0);
	if (image)
	{
		GLenum format;
		if (nrComponents == 1) format = GL_RED;
		else if (nrComponents == 3) format = GL_RGB;
		else if (nrComponents == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(image);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
	}

	return textureID;
}

void init()
{
	std::cout << "Use 'WASD' keys for rotate." << std::endl;
	std::cout << "Press 'k' to see different lights." << std::endl;
	init_camera();
	init_shaders();
	init_light();
	init_cubes();
}

void init_shaders()
{
	// Initialize shaders
	GLuint vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/vertex_shader.glsl");
	GLuint fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/fragment_shader.glsl");
	shader_program = initprogram(vertex_shader, fragment_shader);
}

void init_camera()
{
	// Initialize viewing values
	projection = glm::perspective(glm::radians(60.0f), (float)800 / 800, 0.1f, 1000.0f);
	view = glm::lookAt(eye, vec3(0.0f, 0.0f, 0.0f), up);

	light_dir = eye - vec3(0.f); // Spot light direction is center to eye
}

void init_light()
{
	// Viewing values
	projection_loc = glGetUniformLocation(shader_program, "projection");
	view_loc = glGetUniformLocation(shader_program, "view");

	// Lighting values
	eye_loc = glGetUniformLocation(shader_program, "eye");
	diffuse_loc = glGetUniformLocation(shader_program, "material.diffuse");
	specular_loc = glGetUniformLocation(shader_program, "material.specular");
	shininess_loc = glGetUniformLocation(shader_program, "material.shininess");
	light_pos_loc = glGetUniformLocation(shader_program, "light.position");
	light_amb_loc = glGetUniformLocation(shader_program, "light.ambient");
	light_dif_loc = glGetUniformLocation(shader_program, "light.diffuse");
	light_spe_loc = glGetUniformLocation(shader_program, "light.specular");
	light_mode_loc = glGetUniformLocation(shader_program, "light_mode");
	light_constant_loc = glGetUniformLocation(shader_program, "light.constant");
	light_linear_loc = glGetUniformLocation(shader_program, "light.linear");
	light_quadratic_loc = glGetUniformLocation(shader_program, "light.quadratic");
	light_dir_loc = glGetUniformLocation(shader_program, "light.direction");
	light_cutoff_loc = glGetUniformLocation(shader_program, "light.cutoff");
	light_out_cutoff_loc = glGetUniformLocation(shader_program, "light.out_cutoff");
}

void init_cubes()
{
	for (float i = -10.0f; i < 10.1f; i+=5.0f)
	{
		for (float j = -10.0f; j < 10.1f; j+=5.f)
		{
			GLuint cubeVAO;
			glGenVertexArrays(1, &cubeVAO);
			glBindVertexArray(cubeVAO);

			GLuint VBO, NBO, TBO;

			// Vertices
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0); // Use layout 0 for vertices in vertex shader
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Normals
			glGenBuffers(1, &NBO);
			glBindBuffer(GL_ARRAY_BUFFER, NBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(cube_normals), cube_normals, GL_STATIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Texture coordinates
			glGenBuffers(1, &TBO);
			glBindBuffer(GL_ARRAY_BUFFER, TBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texture_coord), cube_texture_coord, GL_STATIC_DRAW);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

			cubeVAOs.push_back(cubeVAO);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0); // Prevent further modifications

			// Model matrices
			mat4 model = mat4(1.0f);
			model = glm::translate(model, vec3(i, j, 0));
			model = glm::rotate(model, glm::radians(i*30.0f), vec3(1, 1, 0));
			models.push_back(model);
		}
	}
}

void draw_camera()
{
	// Send camera uniforms
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, &(view)[0][0]);
	glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &(projection)[0][0]);
}

void draw_light()
{
	// Send light variables to shader
	glUniform3fv(eye_loc, 1, &eye[0]);
	glUniform1i(diffuse_loc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, load_texture("wood.png")); // Load texture and bind it as diffuse map
	glUniform1i(specular_loc, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, load_texture("canvas.png")); // Load texture and bind it as specular map
	glUniform1f(shininess_loc, shininess);
	glUniform3fv(light_pos_loc, 1, &light_pos[0]);
	glUniform3fv(light_amb_loc, 1, &light_ambient[0]);
	glUniform3fv(light_dif_loc, 1, &light_diffuse[0]);
	glUniform3fv(light_spe_loc, 1, &light_specular[0]);
	glUniform1i(light_mode_loc, light_mode);
	glUniform1f(light_constant_loc, light_constant);
	glUniform1f(light_linear_loc, light_linear);
	glUniform1f(light_quadratic_loc, light_quadratic);
	glUniform3fv(light_dir_loc, 1, &light_dir[0]);
	glUniform1f(light_cutoff_loc, light_cutoff);
	glUniform1f(light_out_cutoff_loc, light_out_cutoff);
}

void draw_cubes()
{
	for (int i = 0; i < 25; i++)
	{
		GLuint model_loc = glGetUniformLocation(shader_program, "model");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &(models[i])[0][0]);

		// Normal matrix
		mat4 normal_matrix = inverse(transpose(models[i]));
		GLuint normal_matrix_loc = glGetUniformLocation(shader_program, "normal_matrix");
		glUniformMatrix4fv(normal_matrix_loc, 1, GL_FALSE, &normal_matrix[0][0]);

		glBindVertexArray(cubeVAOs[i]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0); // Prevent further modifications
	}
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	draw_camera();
	draw_light();
	draw_cubes();

	glutSwapBuffers();

	// Error catch
	GLuint err = glGetError();
	if (err) fprintf(stderr, "%s\n", gluErrorString(err));
}