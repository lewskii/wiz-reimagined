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

enum class EffectType {
  Damage,
  DoT,
  Heal,
  HoT,
  Charm
};

bool IsDamageType(EffectType type);
bool IsHealType(EffectType type);

enum class Target {
  Self,
  Enemy,
  Ally,
  AllEnemies,
  AllAllies
};


class CardEffect {
public:
  virtual ~CardEffect() = default;

  const EffectType type;
  const School school;
  const Target target;

protected:
  CardEffect(EffectType t, School s, Target tgt)
    : type{ t }, school{ s }, target{ tgt } {}
};


class InstantEffect : public CardEffect {
public:
  int strength() { return strength_(); }

protected:
  InstantEffect(EffectType t, School s, Target tgt)
    : CardEffect{ t, s, tgt } {}

  virtual int strength_() const = 0;
};

class VariableDamage final : public InstantEffect {
public:
  VariableDamage(int base, int step, School s, Target tgt)
    : InstantEffect{ EffectType::Damage, s, tgt },
    base_{ base },
    step_{ step }
  {}

  VariableDamage(int base, int step, School s)
    : InstantEffect{ EffectType::Damage, s, Target::Enemy },
    base_{ base },
    step_{ step }
  {}

  VariableDamage(int base, School s, Target tgt)
    : InstantEffect{ EffectType::Damage, s, tgt },
    base_{ base },
    step_{ 10 }
  {}

  VariableDamage(int base, School s)
    : InstantEffect{ EffectType::Damage, s, Target::Enemy },
    base_{ base },
    step_{ 10 }
  {}

private:
  int strength_() const override;

  const int base_;
  const int step_;
};

class FlatDamage final : public InstantEffect {
public:
  FlatDamage(int damage, School s, Target tgt)
    : InstantEffect{ EffectType::Damage, s, tgt },
    damage_{ damage }
  {}

  FlatDamage(int damage, School s)
    : InstantEffect{ EffectType::Damage, s, Target::Enemy },
    damage_{ damage }
  {}

private:
  int strength_() const override { return damage_; }

  const int damage_;
};

class Heal final : public InstantEffect {
public:
  Heal(int heal, Target tgt)
    : InstantEffect{ EffectType::Heal, School::Any, tgt },
    heal_{ heal }
  {}

  Heal(int heal)
    : InstantEffect{ EffectType::Heal, School::Any, Target::Ally },
    heal_{ heal }
  {}

private:
  int strength_() const override { return heal_; }

  const int heal_;
};



class OverTimeEffect : public CardEffect {
public:
  const int strength;
  const int turns;

protected:
  OverTimeEffect(int strength, int turns, EffectType t, School s, Target tgt)
    : CardEffect{ t, s, tgt }, strength{ strength }, turns{ turns }
  {}
};

class DoT final : public OverTimeEffect {
public:
  DoT(int damage, int turns, School s, Target tgt)
    : OverTimeEffect{ damage, turns, EffectType::DoT, s, tgt } {}

  DoT(int damage, School s, Target tgt)
    : OverTimeEffect{ damage, 3, EffectType::DoT, s, tgt } {}

  DoT(int damage, School s)
    : OverTimeEffect{ damage, 3, EffectType::DoT, s, Target::Enemy } {}
};

class HoT final : public OverTimeEffect {
public:
  HoT(int heal, int turns, Target tgt)
    : OverTimeEffect{ heal, turns, EffectType::HoT, School::Any, tgt } {}

  HoT(int heal, Target tgt)
    : OverTimeEffect{ heal, 3, EffectType::HoT, School::Any, tgt } {}

  HoT(int heal)
    : OverTimeEffect{ heal, 3, EffectType::HoT, School::Any, Target::Ally } {}
};



enum class HangingEffectDomain {
  Damage,
  Accuracy,
  Healing
};

std::ostream& operator<<(std::ostream& out, const HangingEffectDomain& t);

class Charm final : public CardEffect {
public:
  Charm(int strength, HangingEffectDomain domain, School s, Target tgt)
    : CardEffect{ EffectType::Charm, s, tgt },
    strength{ strength },
    domain{ domain }
  {}

  Charm(int strength, HangingEffectDomain domain, School s)
    : CardEffect{ EffectType::Charm, s, Target::Ally },
    strength{ strength },
    domain{ domain }
  {}

  const int strength;
  const HangingEffectDomain domain;
};


class HangingEffect {
public:
  const EffectType type;
  const School school;
  const int strength;
  const HangingEffectDomain domain;
  std::string id;

protected:
  HangingEffect(
    EffectType type,
    School school,
    int strength,
    HangingEffectDomain domain,
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
    : HangingEffect{ EffectType::Charm, c.school, c.strength, c.domain, id } {}
};




class HangingOverTime {
public:
  virtual ~HangingOverTime() = default;

  const EffectType type;
  const School school;
  const int per_turn;
  int turns_left;

protected:
  HangingOverTime(const OverTimeEffect& base, EffectType type)
    : type{ type },
    school{ base.school },
    per_turn{ base.strength / base.turns },
    turns_left{ base.turns }
  {}
};

class HangingDoT : public HangingOverTime {
public:
  HangingDoT(const DoT& base) : HangingOverTime{ base, EffectType::DoT } {}
};

class HangingHoT : public HangingOverTime {
public:
  HangingHoT(const HoT& base) : HangingOverTime{ base, EffectType::HoT } {}
};
