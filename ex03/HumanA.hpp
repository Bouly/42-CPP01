#ifndef HUMANA_HPP
# define HUMANA_HPP

# include <string>
# include "Weapon.hpp"

class HumanA
{
	private:
		std::string	name;
		Weapon		&weapon;   // REFERENCE: HumanA is ALWAYS armed (never null)

	public:
		HumanA(std::string name, Weapon &weapon);
		~HumanA();

		void	attack(void);
};

#endif
