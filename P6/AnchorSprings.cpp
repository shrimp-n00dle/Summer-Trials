#include "AnchorSprings.h"

void P6::AnchorSprings::updateForce(MyParticle* particle, float time)
{
	//get current position of the particle
	MyVector pos = particle->Position;

	//create a vector Pos -> anchorPoint
	MyVector force = pos - anchorPoint;

	float mag = force.Magnitude();

	float springForce = -springConstant * abs(mag - restLength);

	//get the direction from the particle to the anchor point
	force = force.Direction();

	force = force.scalarMultiplication(springForce);

	particle->addForce(force);
}
