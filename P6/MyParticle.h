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

	protected:
		bool bDestroy = false;


	/*METHODS*/
	protected:
		void updatePosition(float time);

		void updateVelocity(float time);

	public:
		//Updates the particle and the methods above for EACH PARTICLE
		void updateParticle(float time);

	public:
		void Destroy();

		bool IsDestroyed() { return bDestroy; }
	};
}

