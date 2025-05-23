#include "MyParticle.h"

void  P6::MyParticle::updatePosition(float time)
{
	//P2 = P1 + Velocity * time

	MyVector newAccelValue = Acceleration.scalarMultiplication((time * time));

	Position = Position + Velocity.scalarMultiplication(time) + newAccelValue.scalarMultiplication((1.0f / 2.0f));

}

void  P6::MyParticle::updateVelocity(float time)
{
	/*rate of change in position given the certain time*/

		//V = (P2 - P1) /  time
	Velocity = Velocity + (Acceleration.scalarMultiplication(time));

		//P2 = P1 + Vt

	//Position / time;

}

void P6::MyParticle::updateParticle(float time) 
{
	updatePosition(time);

	updateVelocity(time);
}

void P6::MyParticle::Destroy()
{
	bDestroy = true;
}