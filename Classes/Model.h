#pragma once

#include <glad/glad.h> /*This helps with simplifying runtime when dealing with pointers*/
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../tiny_obj_loader.h"

#include "../Physics/MyVector.h"
#include "Shader.h"

class Model
{
	private:
		/*Attributes*/

		glm::mat4 identity_matrix = glm::mat4(1.0f);

		/*Current positon, transform of the model*/
		glm::mat4 transformation_matrix;

		GLuint VAO, VBO, EBO;

		std::vector<tinyobj::shape_t> objShapes;

		/*Basic Attributes related to mesh*/
		tinyobj::attrib_t attributes;


		std::vector<GLuint> mesh_indicies;

		
	public:
		/*Constructor*/
		Model(std::string name);


		/*Linear Transformation*/
		void MoveModel(Physics::MyVector newPos);
		void scaleModel(Physics::MyVector newScale);
		void rotateModel(Physics::MyVector newAngle, float theta);


		void renderModel(Shader shader);
		void bind(Shader shader);
		void cleanUp();
		
};

