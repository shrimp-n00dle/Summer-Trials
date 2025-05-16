#include "Model.h"


Model::Model() 
{}

void Model::MoveModel(Physics::MyVector newPos)
{
	transformation_matrix = glm::translate(identity_matrix, glm::vec3(newPos));
};

void Model::scaleModel(Physics::MyVector newScale)
{
	transformation_matrix = glm::scale( transformation_matrix, glm::vec3(newScale));
}

void Model::rotateModel(Physics::MyVector newAngle, float theta)
{
	transformation_matrix = glm::rotate(
     transformation_matrix,
	 glm::radians(theta),
	 glm::normalize(glm::vec3(newAngle)));
}

void Model::renderModel(GLuint shader)
{
    //Setting the projection 
    unsigned int projLoc = glGetUniformLocation(shader, "projection");
    glUniformMatrix4fv(projLoc, //Address of the variable
                       1, //How many value are we modifying
                        GL_FALSE, 
                        glm::value_ptr(transformation_matrix)); //Projection Matrix

    //Get the variable named transform from one of the shaders
   //attached to the shaderProg
    unsigned int transformLoc = glGetUniformLocation(shader, "transform");

    //assign the matrix
   glUniformMatrix4fv(transformLoc, //Address to the transform variable
       1, //How many matrices to assign
        GL_FALSE, //Transpose
        glm::value_ptr(transformation_matrix)); // pointer to the matrix
}