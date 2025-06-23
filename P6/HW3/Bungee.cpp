#include "Bungee.h"


/*
* The code given below gives the behavior of a bungee
* Similar to a particle spring BUT the key difference is how it bounces back, theres a restitution of 0.5 
* as bungees (in context to the sample on the ppt) doesnt bouce back beyond the initial anchor point
* 
*/

void P6::Bungee::updateForce(MyParticle* anchor, float time)
{
	//get current position of the particle
	MyVector pos = anchor->Position;

	//correct
	MyVector force = pos - anchorPoint->Position;

	float mag = force.Magnitude();

	//Bounce up is almost half

	float bounceBack;
	//reaches maximum lowest
	if (anchor->Position.y <= -0.69 && !bDown) bDown = true;
	else if (anchor->Position.y <= 0.5f && bDown) bDown = false;
		
	//go down
	if (!bDown) bounceBack = -springLen * abs(mag - restLength);
	//bounce up
	else bounceBack = -(springLen*0.75) * abs(mag - (restLength * 0.2));

	std::cout << anchor->Position.y << std::endl;

	//get the direction from the particle to the anchor point
	force = force.Direction();

	force = force.scalarMultiplication(bounceBack);

	anchor->addForce(force);
}
