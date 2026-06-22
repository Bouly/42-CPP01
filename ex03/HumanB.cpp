#include "HumanB.hpp"
#include <iostream>

// No weapon at construction: the pointer starts at NULL.
HumanB::HumanB(std::string name) : name(name), weapon(NULL)
{
}

HumanB::~HumanB()
{
}

void	HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;   // store the ADDRESS of the given weapon
}

void	HumanB::attack(void)
{
	if (this->weapon != NULL)
		std::cout << this->name << " attacks with their "
				  << this->weapon->getType() << std::endl;
	else
		std::cout << this->name << " has no weapon to attack with" << std::endl;
}
