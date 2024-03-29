#pragma once




enum class School {
  Fire,
  Ice,
  Storm,
  Life,
  Death,
  Myth,
  Any
};

bool SchoolsMatch(School a, School b);


class Effect {
public:
  enum class Type {
    Damage,
    DoT,
    Heal,
    HoT,
    Charm
  };

  enum class Target {
    Self,
    Enemy,
    Ally,
    AllEnemies,
    AllAllies
  };


  virtual ~Effect() = default;

  static constexpr int default_variable_step = 10;
  static constexpr int default_over_time_length = 3;

  const Type type;
  const School school;
  const Target target;

protected:
  Effect(Type t, School s, Target tgt)
    : type{ t }, school{ s }, target{ tgt } {}
};

bool IsDamageType(Effect::Type type);
bool IsHealType(Effect::Type type);



class InstantEffect : public Effect {
public:
  int strength() { return strength_(); }

protected:
  InstantEffect(Type t, School s, Target tgt)
    : Effect{ t, s, tgt } {}

  virtual int strength_() const = 0;
};

class VariableDamage final : public InstantEffect {
public:
  VariableDamage(int base, int step, School s, Target tgt)
    : InstantEffect{ Type::Damage, s, tgt },
    base_{ base },
    step_{ step }
  {}

  VariableDamage(int base, int step, School s)
    : VariableDamage{ base, step, s, Target::Enemy }
  {}

  VariableDamage(int base, School s, Target tgt)
    : VariableDamage{ base, default_variable_step, s, tgt }
  {}

  VariableDamage(int base, School s)
    : VariableDamage{ base, default_variable_step, s, Target::Enemy }
  {}

private:
  int strength_() const override;

  const int base_;
  const int step_;
};

class FlatDamage final : public InstantEffect {
public:
  FlatDamage(int damage, School s, Target tgt)
    : InstantEffect{ Type::Damage, s, tgt },
    damage_{ damage }
  {}

  FlatDamage(int damage, School s)
    : FlatDamage{ damage, s, Target::Enemy }
  {}

private:
  int strength_() const override { return damage_; }

  const int damage_;
};

class Heal final : public InstantEffect {
public:
  Heal(int heal, Target tgt)
    : InstantEffect{ Type::Heal, School::Any, tgt },
    heal_{ heal }
  {}

  Heal(int heal)
    : Heal{ heal, Target::Ally }
  {}

private:
  int strength_() const override { return heal_; }

  const int heal_;
};



class OverTimeEffect : public Effect {
public:
  const int strength;
  const int turns;

protected:
  OverTimeEffect(int strength, int turns, Type t, School s, Target tgt)
    : Effect{ t, s, tgt }, strength{ strength }, turns{ turns }
  {}
};

class DoT final : public OverTimeEffect {
public:
  DoT(int damage, int turns, School s, Target tgt)
    : OverTimeEffect{ damage, turns, Type::DoT, s, tgt } {}

  DoT(int damage, School s, Target tgt)
    : DoT{ damage, default_over_time_length, s, tgt } {}

  DoT(int damage, School s)
    : DoT{ damage, default_over_time_length, s, Target::Enemy } {}
};

class HoT final : public OverTimeEffect {
public:
  HoT(int heal, int turns, Target tgt)
    : OverTimeEffect{ heal, turns, Type::HoT, School::Any, tgt } {}

  HoT(int heal, Target tgt)
    : HoT{ heal, default_over_time_length, tgt } {}

  HoT(int heal)
    : HoT{ heal, default_over_time_length, Target::Ally } {}
};



enum class ModifierDomain {
  Damage,
  Accuracy,
  Healing
};

std::ostream& operator<<(std::ostream& out, const ModifierDomain& t);

class Charm final : public Effect {
public:
  Charm(int strength, ModifierDomain domain, School s, Target tgt)
    : Effect{ Type::Charm, s, tgt },
    strength{ strength },
    domain{ domain }
  {}

  Charm(int strength, ModifierDomain domain, School s)
    : Charm{ strength, domain, s, Target::Ally }
  {}

  const int strength;
  const ModifierDomain domain;
};



class HangingEffect {
public:
  const Effect::Type type;
  const School school;
  const int strength;
  const ModifierDomain domain;
  std::string id;

protected:
  HangingEffect(
    Effect::Type type,
    School school,
    int strength,
    ModifierDomain domain,
    std::string id
  )
    : type{ type },
    school{ school },
    strength{ strength },
    domain{ domain },
    id{ id }
  {}
};

class HangingCharm final : public HangingEffect {
public:
  HangingCharm(Charm c, std::string id)
    : HangingEffect{ Effect::Type::Charm, c.school, c.strength, c.domain, id } {}
};



class HangingOverTime {
public:
  virtual ~HangingOverTime() = default;

  const Effect::Type type;
  const School school;
  const int per_turn;
  int turns_left;

protected:
  HangingOverTime(const OverTimeEffect& base, Effect::Type type)
    : type{ type },
    school{ base.school },
    per_turn{ base.strength / base.turns },
    turns_left{ base.turns }
  {}
};

class HangingDoT : public HangingOverTime {
public:
  HangingDoT(const DoT& base) : HangingOverTime{ base, Effect::Type::DoT } {}
};

class HangingHoT : public HangingOverTime {
public:
  HangingHoT(const HoT& base) : HangingOverTime{ base, Effect::Type::HoT } {}
};
