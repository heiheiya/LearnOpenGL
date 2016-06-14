#define GLEW_STATIC

#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Camera.h"

using namespace std;

//const int screenWidth = 800;
//const int screenHeight = 600;
//
//GLfloat friTri[] =
//{
//	// Positions          // Normals           // Texture Coords
//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
//	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
//	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
//	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
//	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
//
//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//
//	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//
//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
//	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
//	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
//
//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };
//
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//bool keys[1024];
//GLfloat deltaTime = 0.0f;
//GLfloat lastFrame = 0.0f;
//GLfloat lastX = screenWidth / 2.0;
//GLfloat lastY = screenHeight / 2.0;
//
//bool firstMouse = true;
//
//float mixRatio = 0.2;
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	/*GLfloat cameraSpeed = 0.05f;
//	if (key == GLFW_KEY_W)
//	{
//		cameraPos += cameraSpeed * cameraFront;
//	}
//	if (key == GLFW_KEY_S)
//	{
//		cameraPos -= cameraSpeed * cameraFront;
//	}
//	if (key == GLFW_KEY_A)
//	{
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	}
//	if (key == GLFW_KEY_D)
//	{
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	}*/
//	if (action == GLFW_PRESS)
//	{
//		keys[key] = true;
//	}
//	else if (action == GLFW_RELEASE)
//	{
//		keys[key] = false;
//	}
//}
//
//void do_movement()
//{
//	GLfloat cameraSpeed = 5.0f * deltaTime;
//	if (keys[GLFW_KEY_W])
//	{
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	}
//	if (keys[GLFW_KEY_S])
//	{
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	}
//	if (keys[GLFW_KEY_A])
//	{
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	}
//	if (keys[GLFW_KEY_D])
//	{
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//	}
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetKeyCallback(window, key_callback);
//
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK)
//	{
//		cout << "Failed to initialize GLEW" << endl;
//		return -1;
//	}
//
//	glViewport(0, 0, screenWidth, screenHeight);
//
//	glEnable(GL_DEPTH_TEST);
//
//	Shader program1("shader1.vert", "shader1.frag");
//	Shader program2("shader2.vert", "shader2.frag");
//
//	GLuint VAO, VBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(friTri), friTri, GL_STATIC_DRAW);
//	glBindVertexArray(VAO);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindVertexArray(0);
//
//	GLuint lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//	GLuint diffuseMap;
//	glGenTextures(1, &diffuseMap);
//	int width, height;
//	unsigned char* image;
//	image = SOIL_load_image("container2.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, diffuseMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	
//	program1.Use();
//	glUniform1i(glGetUniformLocation(program1.m_program, "material.diffuse"), 0);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwPollEvents();
//
//		GLfloat currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		do_movement();
//		
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		program1.Use();
//		GLint objectColorLoc = glGetUniformLocation(program1.m_program, "objectColor");
//		GLint lightColorLoc = glGetUniformLocation(program1.m_program, "lightColor");
//		GLint lightPosLoc = glGetUniformLocation(program1.m_program, "light.position");
//		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
//		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
//		//lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
//		//lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
//		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
//
//
//		GLint matSpecularLoc = glGetUniformLocation(program1.m_program, "material.specular");
//		GLint matShineLoc = glGetUniformLocation(program1.m_program, "material.shininess");
//
//		glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
//		glUniform1f(matShineLoc, 64.0f);
//
//		GLint lightAmbientLoc = glGetUniformLocation(program1.m_program, "light.ambient");
//		GLint lightDiffuseLoc = glGetUniformLocation(program1.m_program, "light.diffuse");
//		GLint lightSpecularLoc = glGetUniformLocation(program1.m_program, "light.specular");
//		glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
//		glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);
//		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
//		glm::mat4 view;
//		view = camera.GetViewMatrix();
//		glm::mat4 projection;
//		projection = glm::perspective(camera.Zoom, (GLfloat)screenWidth / screenHeight, 0.1f, 100.0f);
//
//		GLuint modelLocation = glGetUniformLocation(program1.m_program, "model");
//		GLuint viewLocation = glGetUniformLocation(program1.m_program, "view");
//		GLint viewPosLoc = glGetUniformLocation(program1.m_program, "viewPos");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
//		glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
//		GLuint projectionLocation = glGetUniformLocation(program1.m_program, "projection");
//		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
//		
//		glm::mat4 model;
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		program2.Use();
//		modelLocation = glGetUniformLocation(program2.m_program, "model");
//		viewLocation = glGetUniformLocation(program2.m_program, "view");
//		projectionLocation = glGetUniformLocation(program2.m_program, "projection");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
//		model = glm::mat4();
//		model = glm::translate(model, lightPos);
//		model = glm::scale(model, glm::vec3(0.2f));
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
//		glBindVertexArray(lightVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();
//	return 0;
//}
//

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool    keys[1024];

// Light attributes
glm::vec3 lightPos(1.0f, 0.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);


	// Build and compile our shader program
	Shader lightingShader("shader1.vert", "shader1.frag");
	Shader lampShader("shader2.vert", "shader2.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions          // Normals           // Texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};
	// First, set the container's VAO (and VBO)
	GLuint VBO, containerVAO;
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(containerVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	// Load textures
	GLuint diffuseMap;
	glGenTextures(1, &diffuseMap);
	int width, height;
	unsigned char* image;
	// Diffuse map
	image = SOIL_load_image("container2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.m_program, "material.diffuse"), 0);


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		do_movement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint lightPosLoc = glGetUniformLocation(lightingShader.m_program, "light.position");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.m_program, "viewPos");
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
		// Set lights properties
		glUniform3f(glGetUniformLocation(lightingShader.m_program, "light.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.m_program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.m_program, "light.specular"), 1.0f, 1.0f, 1.0f);
		// Set material properties
		glUniform3f(glGetUniformLocation(lightingShader.m_program, "material.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.m_program, "material.shininess"), 64.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.m_program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.m_program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.m_program, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		// Draw the container (using container's vertex attributes)
		glBindVertexArray(containerVAO);
		glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.m_program, "model");
		viewLoc = glGetUniformLocation(lampShader.m_program, "view");
		projLoc = glGetUniformLocation(lampShader.m_program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}