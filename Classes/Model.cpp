#include "Model.h"


Model::Model() {}

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