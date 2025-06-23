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

	float currLen, restL;

	//reaches maximum lowest
	if (anchor->Position.y <= -restLength && !bDown)
	{
		bDown = true;
		bStarted = true;
	}

	if (anchor->Position.y >= -1.0f && bDown) 
	{
		currLen = springLen / restLength;
		restL = 0.50f;
	} 
	else { 
		currLen = springLen;
		restL = restLength;
	}



	//Bounce up is almost half

	float bounceBack;
	
	bounceBack = -(currLen * abs(mag - restL));

	//get the direction from the particle to the anchor point
	force = force.Direction();

	//std::cout << force.Direction().y << std::endl;

	force = force.scalarMultiplication(bounceBack);

	anchor->addForce(force);
}
