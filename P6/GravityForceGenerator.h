#pragma once

#include "ForceGenerator.h"


namespace P6
{
	class GravityForceGenerator : public ForceGenerator
	{
		private:
			MyVector Gravity = MyVector(0, -9.8, 0);

		public:
			GravityForceGenerator(const MyVector gravity) : Gravity(gravity) {};
			
			//override
			void updateForce(MyParticle* particle, float time) override;

	};

}

