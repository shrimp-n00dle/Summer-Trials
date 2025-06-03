#pragma once

#include "MyParticle.h"
#include "ForceGenerator.h"

#include "list"


namespace P6
{
	class ForceRegistry
	{
	public:
		void Add(MyParticle* particle, ForceGenerator* generator);
		void Remove(MyParticle* particle, ForceGenerator* generator);
		void Clear();
		void updateForces(float time);
	protected:
		struct ParticleForceRegistry
		{
			MyParticle* particle;
			ForceGenerator* generator;
		};

		std::list<ParticleForceRegistry> Registry;
	};
}


