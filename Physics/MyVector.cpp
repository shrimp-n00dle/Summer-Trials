#include "MyVector.h"

float Physics::MyVector::Magnitude()
{
	magnitude = sqrtf(
						(sqrtf(x) + sqrtf(y) + sqrt(z))
						);

	return magnitude;
}

Physics::MyVector Physics::MyVector::Direction()
{
	return MyVector(x / magnitude, y / magnitude, z / magnitude);
}

Physics::MyVector Physics::MyVector::scalarMultiplication(const float value)
{
	MyVector product(this->x * value, this->y * value, this->z * value);

	return product;
}

Physics::MyVector Physics::MyVector::componentProduct(const MyVector rhs)
{
	MyVector product(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);

	return product;
}


float Physics::MyVector::scalarProduct(const MyVector rhs)
{
	float product = (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);

	return product;
}

Physics::MyVector Physics::MyVector::vectorProduct(const MyVector rhs)
{
	MyVector product (
		(this->y * rhs.z) - (this->z * rhs.y), 
		(this->z * rhs.x) - (this->x * rhs.z),
		(this->x * rhs.y) - (this->y * rhs.x)
	);

	return product;
}
