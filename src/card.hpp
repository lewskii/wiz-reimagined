#pragma once

#include <string>


class Card {
public:
    Card(
        const std::string name,
        const int damage,
        const int accuracy
    )
        :
        name{ name },
        damage{ damage },
        accuracy{ accuracy }
    {}

    const std::string name;
    const int damage;
    const int accuracy;
};