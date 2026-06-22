#include "Zombie.hpp"

int	main(void)
{
	// --- Heap case ---
	// We need the zombie to live AFTER newZombie() returns, so it is
	// allocated with 'new'. Because we own it, we must 'delete' it.
	Zombie	*heapZombie = newZombie("HeapZombie");
	heapZombie->announce();
	delete heapZombie;

	// --- Stack case ---
	// randomChump() only needs the zombie within its own scope, so it is
	// created on the stack and destroyed automatically (no leak possible).
	randomChump("StackZombie");

	return (0);
}
