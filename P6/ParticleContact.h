#pragma once

#include "MyParticle.h"

namespace P6 {
	class ParticleContact
	{
		public:

			//interprenetation depth
			float depth;

			MyParticle* particles[2];
			float restitution;
			MyVector contactNormal;

			void resolve(float time);

		protected:

			//calculates the interpreneatosn resilution
			void resolveInterpenet(float time);

			float GetSeparatingSpeed();
			void resolveVelocity(float time);

	};
}
