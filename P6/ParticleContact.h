#pragma once

#include "MyParticle.h"

namespace P6 {
	class ParticleContact
	{
		public:
			MyParticle* particles[2];
			float restitution;
			MyVector contectNormal;

			void resolve(float time);

		protected:
			float GetSeparatingSpeed();
			void resolveVelocity(float time);

	};
}
