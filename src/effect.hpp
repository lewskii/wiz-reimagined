#pragma once




class Effect {
public:
  enum class Type {
    Damage,
    Heal,
  };

  static Effect Damage(int strength) {
    return Effect{ Type::Damage, strength };
  }

  static Effect Heal(int strength) { 
   return Effect{ Type::Heal, strength };
  }


  const Type type;
  const int strength;

private:
  Effect(Type t, int strength)
    :
    type{ t },
    strength{ strength }
  {}
};