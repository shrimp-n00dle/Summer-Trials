#pragma once

#include "MyVector.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace P6
{
	class MyParticle
	{

	public:

		MyVector AngularVelocity = MyVector(0,0,0);
		float AngularDampening = 0.9f;
		glm::mat4 rotation = glm::mat4(1.0f);

		void AddForceAtPoint(MyVector force, MyVector p);

	protected:
		MyVector accumulatedTorque = MyVector(0, 0, 0);
		virtual float MomentOfIntertia();

	/*ATTRIBUTES*/
	public:
		

		float radius = 1.0f;

		float restitution = 1.0f;

		float mass = 0;

		MyVector Position;

		MyVector Velocity;

		float damping = 0.9f;

		MyVector Acceleration;

		bool bBoost = false;

	protected:
		bool bDestroy = false;


	/*METHODS*/
	protected:
		//force gathered before the FIXED update
		MyVector accumulatedForce = MyVector(0, 0, 0);

		void updatePosition(float time);

		void updateVelocity(float time);

	public:
		//Updates the particle and the methods above for EACH PARTICLE
		void updateParticle(float time);

		void addForce(MyVector force);
		void resetForce();

		float randomAccel();

	public:
		void Destroy();

		bool IsDestroyed() { return bDestroy; }
	};
}

