#pragma once

#include <glad/glad.h> /*This helps with simplifying runtime when dealing with pointers*/
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../tiny_obj_loader.h"

#include "../Physics/MyVector.h"

class Model
{
	private:
		/*Attributes*/
		glm::mat4 identity_matrix = glm::mat4(1.0f);

		/*Current positon, transform of the model*/
		glm::mat4 transformation_matrix;
	public:
		/*Constructor*/
		Model();


		/*Linear Transformation*/
		void MoveModel(Physics::MyVector newPos);
		void scaleModel(Physics::MyVector newScale);
		void rotateModel(Physics::MyVector newAngle, float theta);
		void renderModel(GLuint shader);
		
};

