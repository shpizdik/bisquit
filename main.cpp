#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>

const int PRM_WIDTH = 1280;
const int PRM_HEIGHT = 720;

int main(){
	//GLFW initialization & window creation
	//-------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(PRM_WIDTH, PRM_HEIGHT, "gavno suka", NULL, NULL);

	if(window == NULL){
		std::cout << "failed to create glfwindow" << std::endl;
		return -1;
	}

	glfwSetWindowPos(window, 0, 0);
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}

	glViewport(0, 0, PRM_WIDTH, PRM_HEIGHT);

	//main loop
	while (!glfwWindowShouldClose(window)){
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.0f, 0.0f, 0.0f, 10.0f);
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

		glfwSwapBuffers(window);
		glfwPollEvents();

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
		glGenBUffers(1, &VBO);
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

	}
		glfwTerminate();

	return 0;
}