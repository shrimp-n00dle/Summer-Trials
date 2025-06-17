#pragma once

#include "MyParticle.h"
#include "ParticleContact.h"

namespace P6
{
	class ParticleLink
	{
	public:
		MyParticle* particles[2];

		virtual ParticleContact* GetContact() { return nullptr; };

	protected:
		float currentLength();

	};
}

