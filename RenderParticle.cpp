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
		std::cout << PhysicsParticle->Position.x << "  " << PhysicsParticle->Position.y << "  " << PhysicsParticle->Position.z << "  " << std::endl;
		
		/*SCALE*/
		model->scaleModel(P6::MyVector(0.5f, 0.5f, 0.5f));

		model->renderModel();
	}
}
