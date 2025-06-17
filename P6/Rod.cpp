#include "Rod.h"

P6::ParticleContact* P6::Rod::GetContact()
{
	float currLen = currentLength();

	if (currLen == length)
	{
		return nullptr;
	}

	ParticleContact* ret = new ParticleContact();
	ret->particles[0] = particles[0];
	ret->particles[1] = particles[1];

	MyVector dir = particles[1]->Position - particles[0]->Position;

	dir = dir.Direction();


	if (currLen > length)
	{
		ret->contactNormal = dir;

		ret->depth = currLen - length;
	}

	else
	{
		ret->contactNormal = dir.scalarMultiplication(-1.0f);
		ret->depth = length - currLen;
	}

	ret->restitution = restitution;

	return ret;

}
