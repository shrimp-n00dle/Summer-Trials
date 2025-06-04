#include "RenderParticle.h"

void RenderParticle::Draw()
{
	if (!PhysicsParticle->IsDestroyed())
	{
		/*COLOR*/
		//model or particle? MODEL MUNA
		model->setColor(Color);

		/*POSITION*/
		model->moveModel(PhysicsParticle->Position);
		//std::cout << PhysicsParticle->Position.x << "  " << PhysicsParticle->Position.y << "  " << PhysicsParticle->Position.z << "  " << std::endl;
		
		/*SCALE*/
		model->scaleModel(P6::MyVector(0.20f, 0.20f, 0.20f));

		model->renderModel();
	}
}

int RenderParticle::recordTime(float value, int rank)
{
	if (!bRecorded)
	{
		std::cout << PhysicsParticle->Position.x << std::endl;
		rank++;
		std::cout << Name << "Rank: " << rank << " ,total time: " << value << "seconds" << std::endl;

		bRecorded = true;

		
	}

	return rank;
}
