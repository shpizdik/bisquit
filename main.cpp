#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int PRM_WIDTH = 1280;
const int PRM_HEIGHT = 720; //PRM stands for 'parameter'

GLfloat vertices[] = {
	-0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.0f, -0.5f, 0.0f
}; //vertex coordinates specification

GLuint VBO; //will further be used to generate vertex buffers
GLuint vertexShader; //shader object itself

//reading shader
GLchar vertexShaderSource;
std::ifstream vertexShaderFile;

vertexShaderFile.open("shader.vert");
std::stringstream vertexShaderStream;
vertexShaderStream << vertexShaderFile.rdbuf();
vertexShaderFile.close();
vertexShaderSource = vertexShaderStream.str();





int main(){

	//GLFW window initialization and render context creation block
	//------------------------------------------------------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(PRM_WIDTH, PRM_HEIGHT, "My Window", NULL, NULL);

	if(window == NULL){
		std::cout << "GLFW window creation failed" << std::endl;
		return -1;
	}

	glfwSetWindowPos(window, 0, 0);
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}

	glViewport(0, 0, PRM_WIDTH, PRM_HEIGHT);
	//------------------------------------------------------------------------------------


	//BUFFER PROBLEM FIXED: moved here from after declaring VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies user-specified vertex data into the buffer 

	//Shader compilation
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //create shader context i suppose
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //shder source code loading
	glCompileShader(vertexShader); //pretty straightforward i guess


	//debug info
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}






	while (!glfwWindowShouldClose(window)){
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		//checking and calling events
		glfwPollEvents();

		glClearColor(0.3f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); //always clear, or previous iteration results will still be seen

		//buffer swapping
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}