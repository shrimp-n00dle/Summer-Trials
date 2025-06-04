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

void RenderParticle::recordTime(float value)
{
	if (!bRecorded)
	{
		counter++;

		std::cout << Name << "Rank: " << counter << " ,total time: " << value << "seconds" << std::endl;

		bRecorded = true;
	}

}
