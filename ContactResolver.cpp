#include "ContactResolver.h"


void ContactResolver::resolveContacts(std::vector<P6::ParticleContact*> contacts, float time)
{

	//Assign the least speed to the first value
	leastSSpeed = contacts[0]->GetSeparatingSpeed();

	//if resolve count > limit
	if (current_iterations < max_iterations)
	{
		for (unsigned i = 0; i < contacts.size(); i++)
		{
			//Get the Contact with the LEAST Separating Speed
			float currSpeed = contacts[i]->GetSeparatingSpeed();

			if (leastSSpeed >= currSpeed) leastSSpeed = currSpeed;

		}

		//Resolve that Contact
		for (unsigned i = 0; i < contacts.size(); i++)
		{
			float currSpeed = contacts[i]->GetSeparatingSpeed();
			if (leastSSpeed == currSpeed)
			{
				contacts[i]->resolve(time);

				//Increment resolve count
				current_iterations++;
				return;
			}
		}

	}

	




	//for (unsigned i = 0; i < contacts.size(); i++)
	//{
	//	//If Resolve Count > Limit OR if the Separating Speed of the current Contacts >= 0 - End
	//	if (current_iterations > max_iterations || contacts[i]->GetSeparatingSpeed() >= 0 && contacts[i]->depth <= 0)
	//	{
	//		std::cout << "RETUTN" << std::endl;
	//		return;
	//	}
	//	else
	//	{
	//		//Get the Contact with the LEAST Separating Speed
	//		float currSpeed = contacts[i]->GetSeparatingSpeed();

	//		

	//		if (leastSSpeed >= currSpeed)
	//		{

	//			leastSSpeed = currSpeed;

	//	
	//			//Resolve that Contact
	//			contacts[i]->resolve(time);

	//			//Increment resolve count
	//			current_iterations++;

	//		
	//		}
	//		//OR the Contact with Depth > 0
	//		else if (contacts[i]->depth > 0)
	//		{
	//			//Resolve that Contact
	//			contacts[i]->resolve(time);

	//			//Increment resolve count
	//			current_iterations++;
	//		}

	//	}	
	//}

}