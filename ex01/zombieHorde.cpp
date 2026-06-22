#include "Zombie.hpp"

// Allocates N zombies in a SINGLE allocation (one 'new[]', not N times 'new').
// Each zombie is then named, and a pointer to the first one is returned.
// The caller MUST free the horde with 'delete[]' (not 'delete').
Zombie	*zombieHorde(int N, std::string name)
{
	if (N <= 0)
		return (NULL);

	Zombie	*horde = new Zombie[N];

	for (int i = 0; i < N; i++)
		horde[i].setName(name);
	return (horde);
}
