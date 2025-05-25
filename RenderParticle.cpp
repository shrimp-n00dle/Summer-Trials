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

		model->renderModel();
	}
}
