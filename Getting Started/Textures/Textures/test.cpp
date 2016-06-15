#define GLEW_STATIC

#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include "shader.h"

using namespace std;

GLfloat friTri[] =
{
	//first              //color            //Texture coord
	-1.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	0.0f, 0.5f, 0.0f , 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 
	-1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f };

GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
};

GLfloat secTri[]=
{
	//second
	0.0f, -0.5f, 0.0f,
	1.0f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f };

GLfloat texCoords[] = {
	0.0f, 0.0f,  // Lower-left corner  
	1.0f, 0.0f,  // Lower-right corner
	0.5f, 1.0f   // Top-center corner
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	Shader program1("shader.vert", "shader1.frag");
	Shader program2("shader.vert", "shader2.frag");

	GLuint VAO[2], VBO[2],EBO;
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(friTri), friTri, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secTri), secTri, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image1 = SOIL_load_image("../../../textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* image2 = SOIL_load_image("../../../textures/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		program1.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(program1.m_program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(program1.m_program, "ourTexture2"), 1);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLfloat yOffset = -0.5;
		GLint vertexColorLocation = glGetUniformLocation(program2.m_program, "ourColor");
		GLint yOffsetLocation = glGetUniformLocation(program2.m_program, "yoffset");
		program2.Use();
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glUniform1f(yOffsetLocation, yOffset);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}