#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>

const int PRM_WIDTH = 856;
const int PRM_HEIGHT = 480;

int main(){
	//GLFW initialization & window creation
	//-------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(PRM_WIDTH, PRM_HEIGHT, "gavno suka", NULL, NULL);

	if(window == NULL){
		std::cout << "failed to create glfw window" << std::endl;
		return -1;
	}

	glfwSetWindowPos(window, 0, 0);
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}

	glViewport(0, 0, PRM_WIDTH, PRM_HEIGHT);





		//making a triangle
		//-----------------
		float vertices[] = {
			// positions		// colors
			0.7f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.7f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		//vertex array
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//vertex buffer
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);


		//Shader Enabling
		//---------------
		// reading shaders
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		
		try{
			// opening files
			vShaderFile.open("shaders/shader.vert");
			fShaderFile.open("shaders/shader.frag");
			std::stringstream vShaderStream, fShaderStream;
			//read file's buffer contents into stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close files
			vShaderFile.close();
			fShaderFile.close();
			//convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::istream::failure e){
			std::cout << "ERROR: SHADER FILE NOT READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//create vertex shader
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		int success; //i genuinely want to rename it to succ_ass but uh erm nah brah
		char infoLog[512];
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		//print compile errors if any
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR: VERTEX SHADER COMPILATION FAILED" << infoLog << std::endl;
		};

		//create fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		//print compile errors if any
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR: FRAGMENT SHADER COMPILATION FAILED" << infoLog << std::endl;
		};


		//shader program
		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		//print linking errors if any
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if(!success){
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR: SHADER PROGRAM LINKING FAILED" << infoLog << std::endl;
		};

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);



		//Texture parameters and loading
		//------------------------------
		GLfloat textureCords[] = {
			0.0f, 0.0f,
			1.0f, 0.0f, 
			0.5f, 1.0f
		};

		// glTexParameteri(GL_TEXTURE_2D, GL_WRAP_S GL_CLAMP_TO_BORDER);
		// glTexParameteri(GL_TEXTURE_2D, GL_WRAP_T, GL_CLAMP_TO_BORDER);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);


		//todo: write and image loader myself and delete the fuck outta SOIL



	//main loop
	while (!glfwWindowShouldClose(window)){
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// //Legacy OpenGL triangle render
		// //-----------------------------
		// glBegin(GL_TRIANGLES);
		// glVertex2f(-0.5f, -0.5f);
		// glVertex2f(0.0f, -0.5f);
		// glVertex2f(0.5f, -0.5f);
		// glEnd();
		// //-----------------------------
		// //note: it doesn't fucking work, gotta find out why
		// //i'll leave these 5 lines here for possible reference

		//doing some sneaky shader stuff
		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
		glfwTerminate();

	return 0;
}