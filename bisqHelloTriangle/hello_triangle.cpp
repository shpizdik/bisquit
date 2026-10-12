#include <iostream>
#include "hello_triangle.h"
// #include <glad/glad.h>


void PrintZaebisIfWorks(){
	std::cout << "Zaebis yopta" << std::endl;
}

// void bisqHelloTriangle(unsigned int VAO, unsigned int VBO){
// 		float vertices[] = {
// 			// positions		// colors
// 			0.7f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
// 			-0.7f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
// 			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
// 		};

// 		//vertex array
// 		unsigned int VAO;
// 		glGenVertexArrays(1, &VAO);
// 		glBindVertexArray(VAO);

// 		//vertex buffer
// 		unsigned int VBO;
// 		glGenBuffers(1, &VBO);
// 		glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 		//position
// 		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
// 		glEnableVertexAttribArray(0);

// 		//color
// 		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
// 		glEnableVertexAttribArray(1);
// }