

#include <iostream>
#include <string>
#include <vector>


class Card {
public:
  Card(
    const std::string name,
    const int damage
  )
    :
    name{ name },
    damage{ damage }
  {}

  const std::string name;
  const int damage;
};




class Wizard {
public:
  static const int max_pips = 7;

  Wizard(const std::string name, const int hp)
    :
    name{ name },
    health{ hp }
  {}

  int DealDamage(int damage) {
    int dealt = std::min(damage, health);
    health -= dealt;
    return dealt;
  }

  const std::string name;
  int health;

  std::vector<Card> deck;
};




void Cast(const Card card, Wizard &target) {
  int damage = target.DealDamage(card.damage);
  std::cout << target.name << " took " << damage << " damage from " << card.name << "!\n";
  if (target.health == 0)
    std::cout << target.name << " has been defeated!\n";
}




int main()
{
  Card fire_cat{ "fire cat", 100 };
  Card thunder_snake{ "thunder snake", 125 };

  Wizard red{ "red", 491};
  Wizard blue{ "blue", 449};
  std::vector<Wizard*> players{ &red, &blue };

  red.deck.push_back(fire_cat);
  blue.deck.push_back(thunder_snake);


  size_t player_count = players.size();

  while (red.health > 0 && blue.health > 0) {
    for (size_t i = 0; i < player_count; ++i) {
      Wizard w = *players[i];
      std::cout << w.name << "'s hp: " << w.health << "\n";
    }

    for (size_t i = 0; i < player_count; ++i) {
      Wizard w = *players[i];
      if (w.health > 0) {
        Cast(w.deck[0], *players[(i + 1) % player_count]);
      }
    }

    std::cin.ignore();
  }

  if (red.health > 0)
    std::cout << "red wins!";
  else
    std::cout << "blue wins!";
}

