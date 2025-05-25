#pragma once
#include "P6/MyVector.h"
#include "P6/MyParticle.h"
#include "Classes/Model.h"

//using namespace P6;

class RenderParticle
{
public:

	/*ATTRIBUTES*/
	P6::MyParticle* PhysicsParticle;

	Model* model;

	P6::MyVector Color;

public:
	/*METHODS*/
	RenderParticle(P6::MyParticle* particle, Model* currModel) : PhysicsParticle(particle), model(currModel) 
	{
		Color = P6::MyVector(1, 1, 1);
	}

	RenderParticle(P6::MyParticle* particle, Model* currModel, P6::MyVector currColor) : PhysicsParticle(particle), model(currModel), Color(currColor) {};

	void Draw();



};

