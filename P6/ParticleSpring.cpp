#include "ParticleSpring.h"

void P6::ParticleSpring::updateForce(MyParticle* particle, float time)
{
	//get current position of the particle
	MyVector pos = particle->Position;

	MyVector force = pos - otherParticle->Position;

	float mag = force.Magnitude();

	float springForce = -springConstant * abs(mag - restLength);

	//get the direction from the particle to the anchor point
	force = force.Direction();

	force = force.scalarMultiplication(springForce);

	particle->addForce(force);
}