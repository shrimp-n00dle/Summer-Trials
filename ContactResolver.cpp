#include "ContactResolver.h"


void ContactResolver::resolveContacts(std::vector<P6::ParticleContact*> contacts, float time)
{

	//Assign the least speed to the first value
	leastSSpeed = contacts[0]->GetSeparatingSpeed();


	for (unsigned i = 0; i < contacts.size(); i++)
	{
		//If Resolve Count > Limit OR if the Separating Speed of the current Contacts >= 0 - End
		if (i > max_iterations || contacts[i]->GetSeparatingSpeed() >= 0)
		{
			return;
		}
		else
		{
			//Get the Contact with the LEAST Separating Speed
			float currSpeed = contacts[i]->GetSeparatingSpeed();

			if (leastSSpeed >= currSpeed)
			{
				leastSSpeed = currSpeed;

				//Resolve that Contact
				contacts[i]->resolve(time);
			}

		}
			
	

		
	}

	//
}