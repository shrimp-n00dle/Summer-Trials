#include "PhysicsWorld.h"

void P6::PhysicsWorld::addParticle(P6::MyParticle* particle)
{
	particleList.push_back(particle);

	forceRegistry.Add(particle, &Gravity);
}

void P6::PhysicsWorld::AddContact(MyParticle* p1, MyParticle* p2, float restitution, MyVector contactNormal)
{
	ParticleContact* toAdd = new ParticleContact();

	//Assign needed variables and values
	toAdd->particles[0] = p1;
	toAdd->particles[1] = p2;
	toAdd->restitution = restitution;
	toAdd->contactNormal = contactNormal;

	Contacts.push_back(toAdd);
}

void P6::PhysicsWorld::Update(float time)
{
	updateParticleList();

	forceRegistry.updateForces(time);

	for (std::list<MyParticle*>::iterator p = particleList.begin();
		//If its not the end, move to the next particle
		p != particleList.end(); p++)
	
	{
		//std::cout << "COUNTER: " << *p << std::endl;
		/*Call the update*/
		(*p)->updateParticle(time);
	}

	//call generate contacts here
	generateContacts();

	if (Contacts.size() > 0)
	{
		contactResolver.resolveContacts(Contacts, time);
	}
}

void P6::PhysicsWorld::updateParticleList()
{
	particleList.remove_if( 
		
		[](MyParticle* p)
			{
			return p->IsDestroyed();
			}
	);

}

void P6::PhysicsWorld::generateContacts()
{
	Contacts.clear();

	for (std::list<ParticleLink*>::iterator i = Links.begin(); i != Links.end(); i++)
	{
		ParticleContact* contact = (*i)->GetContact();

		if (contact != nullptr)
		{
			Contacts.push_back(contact);
		}
	}
}
