#include "Zombie.hpp"
#include <iostream>

// Default constructor: REQUIRED because 'new Zombie[N]' can only call the
// constructor with no arguments. The name is set afterwards via setName().
Zombie::Zombie()
{
}

Zombie::~Zombie()
{
	std::cout << this->name << " is now destroyed" << std::endl;
}

void	Zombie::setName(std::string name)
{
	this->name = name;
}

void	Zombie::announce(void)
{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
