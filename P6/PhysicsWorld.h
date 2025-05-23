#pragma once
#include <list>
#include "MyParticle.h"

namespace P6
{
	class PhysicsWorld
	{
		public:
			std::list<MyParticle*> particleList;

			void addParticle(MyParticle* particle);

			//Calls the UPDATE OF ALL
			void Update(float time);

		private:
			void updateParticleList();
	};
}


