#include "Chain.h"


/*
* The code given below gives the behavior of a bungee
* it continues to follow gravitational force until it reaches its lowest point
*
*/

void P6::Chain::updateForce(MyParticle* anchor, float time)
{

	if (bDrop)
	{
		anchor->resetForce();
		anchor->Position = freezePos;
		return;
	}
	//get current position of the particle
	MyVector pos = anchor->Position;

	//correct
	MyVector force = pos - anchorPoint->Position;

	mag = force.Magnitude();

	float bounceBack = -springLen * abs(mag - restLength);

	if ((mag - restLength) >= 0.11) 
	{
		freezePos = anchor->Position;
		bDrop = true;
	} 


	//get the direction from the particle to the anchor point
	force = force.Direction();

	force = force.scalarMultiplication(bounceBack);

	anchor->addForce(force);
}
