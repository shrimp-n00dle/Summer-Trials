#pragma once

#include "MyVector.h"

namespace P6
{
	class MyParticle
	{

	/*ATTRIBUTES*/
	public:
		float mass = 0;

		MyVector Position;

		MyVector Velocity;

		MyVector Acceleration;


	/*METHODS*/
	protected:
		void updatePosition(float time);

		void updateVelocity(float time);

	public:
		//Updates the particle and the methods above
		void Update(float time);
	};
}

