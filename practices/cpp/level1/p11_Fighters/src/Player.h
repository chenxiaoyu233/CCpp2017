#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"

class Player: public Character{
	private:
		sf::Clock life_clock;
	public:
		Player(int kind, string name, sf::Vector2f pos, Director *world);
		virtual void Action(sf::Time dt,sf::Vector2f pos);
		virtual void display();
		virtual void set_life_bar(string setting, sf::Vector2f pos);
		//virtual void be_impacted_from(Item *other);
		void fire(sf::Time dt, sf::Vector2f dir);
		void set_skill();
};



#endif
