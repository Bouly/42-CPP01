#ifndef HUMANB_HPP
# define HUMANB_HPP

# include <string>
# include "Weapon.hpp"

class HumanB
{
	private:
		std::string	name;
		Weapon		*weapon;   // POINTER: HumanB may have NO weapon (can be NULL)

	public:
		HumanB(std::string name);
		~HumanB();

		void	setWeapon(Weapon &weapon);
		void	attack(void);
};

#endif
