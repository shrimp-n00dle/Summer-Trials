#pragma once

#include "MyVector.h"

namespace P6
{
	class EngineParticle
	{

		/*ATTRIBUTES*/
	public:

		float lifespan = 0;

		MyVector Acceleration;

		MyVector Position;

		MyVector Velocity;

		float damping = 0.9f;

		/*OPTIONAL*/
		float mass = 1.0f;


	protected:
		bool bDestroy = false;


		/*METHODS*/
	protected:

		void updatePosition(float time);

		void updateVelocity(float time);

	public:

		//Updates the particle and the methods above for EACH PARTICLE
		void updateParticle(float time);

		void addForce(MyVector force);
		void resetForce();

		float randomAccel();

		void removeParticle();

	public:
		void Destroy();

		bool IsDestroyed() { return bDestroy; }
	};
}

