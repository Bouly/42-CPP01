#include "Zombie.hpp"

// Allocates a Zombie on the HEAP so it survives after this function returns.
// The caller becomes the owner and is responsible for 'delete'.
Zombie	*newZombie(std::string name)
{
	return (new Zombie(name));
}
