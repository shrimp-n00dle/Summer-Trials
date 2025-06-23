#pragma once
#include "../ForceGenerator.h"

namespace P6
{
	class Bungee : public ForceGenerator
	{
	private:

		MyParticle* anchorPoint;

		//length of the spring and rest length
		float springLen,restLength;

	

	public:

		bool bDown = false;
		bool bStarted = false;
		Bungee(MyParticle* anchor, float length, float rlength)
		{
			anchorPoint = anchor;
			springLen = length;
			restLength = rlength;
		}

		//override
		void updateForce(MyParticle* particle, float time) override;
	};
}


