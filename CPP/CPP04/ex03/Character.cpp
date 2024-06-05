#include "Character.hpp"

Character::Character() : _name("defaultName")
{
	std::cout << "Character default constructor called" << std::endl;
    for (int i = 0; i < 4; ++i) 
    {
        _inventory[i] = NULL;
        _ground[i] = NULL;
    }
}

Character::Character(std::string name) : _name(name)
{
	std::cout << "Character " << _name << " constructor called" << std::endl;
    for (int i = 0; i < 4; ++i) 
    {
        _inventory[i] = NULL;
        _ground[i] = NULL;
    }
}

Character::Character(const Character &src)
{
	std::cout << "Character copy constructor called" << std::endl;
    _name = src._name;
    for (int i = 0; i < 4; ++i) 
    {
        if (src._inventory[i])
            _inventory[i] = src._inventory[i]->clone();
        else
            _inventory[i] = NULL;
    }
    for (int i = 0; i < 4; ++i) 
    {
        if (src._ground[i])
            _ground[i] = src._ground[i]->clone();
        else
            _ground[i] = NULL;
    }
}

Character::~Character()
{
	std::cout << "Character " << _name << " destructor called" << std::endl;
    for (int i = 0; i < 4; ++i) 
    {
        delete _inventory[i];
    }
    for (int i = 0; i < 4; ++i) 
    {
        delete _ground[i];
    }
}

Character &Character::operator=(const Character &rhs)
{
	std::cout << "Character copy assignment operator called" << std::endl;
    if (this != &rhs) 
    {
        for (int i = 0; i < 4; ++i) 
        {
            delete _inventory[i];
        }
        for (int i = 0; i < 4; ++i) 
        {
            delete _ground[i];
        }
        _name = rhs._name;
        for (int i = 0; i < 4; ++i) 
        {
            if (rhs._inventory[i])
                _inventory[i] = rhs._inventory[i]->clone();
            else
                _inventory[i] = NULL;
        }
        for (int i = 0; i < 4; ++i) 
        {
            if (rhs._ground[i])
                _ground[i] = rhs._ground[i]->clone();
            else
                _ground[i] = NULL;
        }
    }
    return *this;
}

	
std::string const &Character::getName() const
{
	return (_name);
}

void Character::equip(AMateria* m)
{
	if (!m)
		std::cout << _name << " doesn't learned this materia !" << std::endl;
	for (size_t i = 0; i < sizeof(_inventory) / sizeof(_inventory[0]) ; i++)
	{
		if (!_inventory[i])
		{
			_inventory[i] = m;
			std::cout << _name << " equip the " << m->getType() << " material in the slot number " << i << "." << std::endl;
			return;
		}
	}
	std::cout << _name << " can not equip the " << m->getType() << " material. Inventory is full." << std::endl;
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= (int)(sizeof(_ground) / sizeof(_ground[0])))
    {
        std::cout << "There is no slot " << idx << " !" << std::endl;
        return;
    }

    if (!_inventory[idx])
    {
        std::cout << "* There's nothing to unequip at slot " << idx << " !" << std::endl;
        return;
    }

    for (size_t i = 0; i < sizeof(_ground) / sizeof(_ground[0]); ++i)
    {
        if (!_ground[i])
        {
            _ground[i] = _inventory[idx]->clone();
            delete _inventory[idx];
            _inventory[idx] = NULL;
            std::cout << getName() << " unequipped " << _ground[i]->getType() << " !" << std::endl;
            return;
        }
    }

    // Si aucun emplacement vide n'est trouvé sur le sol, déplacez l'équipement à l'emplacement 0
    delete _ground[0];
    _ground[0] = _inventory[idx]->clone();
    delete _inventory[idx];
    _inventory[idx] = NULL;
    std::cout << getName() << " unequipped " << _ground[0]->getType() << " !" << std::endl;
}


void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= (int)(sizeof(_ground) / sizeof(_ground[0])))
    {
        std::cout << "There is no slot " << idx << " !" << std::endl;
        return;
    }
	std::cout << _name << "uses " << _inventory[idx] << " against " << target.getName() << std::endl;
	_inventory[idx]->use(target);
}
