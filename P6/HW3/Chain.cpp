#include "Chain.h"


/*
* The code given below gives the behavior of a bungee
* Similar to a particle spring BUT the key difference is how it bounces back, theres a restitution of 0.5
* as bungees (in context to the sample on the ppt) doesnt bouce back beyond the initial anchor point
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

	std::cout << mag - restLength << std::endl;

	//get the direction from the particle to the anchor point
	force = force.Direction();

	/*std::cout << force.Direction().y << std::endl;*/

	force = force.scalarMultiplication(bounceBack);

	anchor->addForce(force);
}
