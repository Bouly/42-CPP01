#include "Zombie.hpp"
#include <iostream>

int	main(void)
{
	int		N = 5;
	Zombie	*horde = zombieHorde(N, "HordeZombie");

	if (horde == NULL)
	{
		std::cout << "Failed to create the horde." << std::endl;
		return (1);
	}

	// Make every zombie of the horde announce itself.
	for (int i = 0; i < N; i++)
		horde[i].announce();

	// ONE delete[] frees the whole array (and calls every destructor).
	delete [] horde;

	return (0);
}
