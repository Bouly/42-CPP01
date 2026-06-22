#include "Zombie.hpp"

// Allocates a Zombie on the STACK. It is only needed inside this function,
// so it is destroyed automatically when the function returns (no delete).
void	randomChump(std::string name)
{
	Zombie	zombie(name);

	zombie.announce();
}
