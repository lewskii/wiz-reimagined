#pragma once




class Effect {
public:
  enum class Type {
    Damage
  };

  static Effect Damage(int strength) { return Effect{ Type::Damage, strength }; }


  const Type type;
  const int strength;

private:
  Effect(Type t, int strength)
    :
    type{ t },
    strength{ strength }
  {}
};