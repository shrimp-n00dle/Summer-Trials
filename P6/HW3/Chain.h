#pragma once
#include "../ForceGenerator.h"

namespace P6
{
	class Chain : public ForceGenerator
	{
	private:
		
		MyParticle* anchorPoint;

		//length of the spring and rest length
		float springLen, restLength, mag = 0.0f;

		bool bDrop = false;

		MyVector freezePos;





	public:
		Chain(MyParticle* anchor, float length, float rlength)
		{
			anchorPoint = anchor;
			springLen = length;
			restLength = rlength;

		}

		//override
		void updateForce(MyParticle* particle, float time) override;
	};

}


