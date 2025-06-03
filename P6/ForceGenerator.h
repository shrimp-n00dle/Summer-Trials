#pragma once

#include "MyParticle.h"

namespace P6
{
	class ForceGenerator
	{
	public:

		virtual void updateForce(MyParticle* p, float time)
		{
			p->addForce(MyVector(0, 0, 0));
		}

		
		//overload
		// void UpdateForce(float time)
		//{
			//do something else
		//};

	};
}

