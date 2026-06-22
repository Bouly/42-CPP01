#include "HumanA.hpp"
#include <iostream>

// A reference member MUST be initialized in the initialization list:
// it cannot be left unset, and it can never be re-bound to another object.
HumanA::HumanA(std::string name, Weapon &weapon) : name(name), weapon(weapon)
{
}

HumanA::~HumanA()
{
}

void	HumanA::attack(void)
{
	std::cout << this->name << " attacks with their "
			  << this->weapon.getType() << std::endl;
}
