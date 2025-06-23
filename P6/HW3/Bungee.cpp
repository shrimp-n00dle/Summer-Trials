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
		std::cout << "LOWEST POITN" << std::endl;
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

	if (bDown)
	{
		std::cout << "BOINCE NACK IS " << bounceBack << std::endl;
		std::cout << anchor->Position.y << std::endl;
	}



	//reaches maximum lowest
	//if (anchor->Position.y <= -restLength && !bDown)
	//{
	//	std::cout << "LOWEST POITN" << std::endl;
	//	bDown = true;
	//	bStarted = true;
	//}
	//else if (anchor->Position.y >= 0.0f && bDown) bDown = false;
	//	
	////go down
	//if (!bStarted) bounceBack = -springLen * abs(mag - restLength);
	////bounce up
	//else if (bDown)
	//{
	//	bounceBack = -(springLen * 0.75) * abs(mag - (restLength * 0.75));
	//	std::cout << anchor->Position.y << std::endl;
	//}
	//else if (bStarted) { 
	//	bounceBack = -(springLen /100) * abs(mag - (restLength /100)); 
	//	std::cout << "NEW " << bounceBack << std::endl;
	//}


	//std::cout << anchor->Position.y << std::endl;

	//get the direction from the particle to the anchor point
	force = force.Direction();

	//std::cout << force.Direction().y << std::endl;

	force = force.scalarMultiplication(bounceBack);

	anchor->addForce(force);
}
