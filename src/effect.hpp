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

class CardEffect {
public:
  virtual ~CardEffect() = default;

  const EffectType type;
  const School school;

protected:
  CardEffect(EffectType t, School school) : type{ t }, school{ school } {}
};


class InstantEffect : public CardEffect {
public:
  int strength() { return strength_(); }

protected:
  InstantEffect(EffectType t, School school) : CardEffect{ t, school } {}

  virtual int strength_() const = 0;
};

class VariableDamage final : public InstantEffect {
public:
  VariableDamage(int base, int step, School school)
    : InstantEffect{ EffectType::Damage, school },
    base_{ base },
    step_{ step }
  {}
  VariableDamage(int base, School school)
    : InstantEffect{ EffectType::Damage, school },
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
  FlatDamage(int damage, School school)
    : InstantEffect{ EffectType::Damage, school }, damage_{ damage } {}

private:
  int strength_() const override { return damage_; }

  const int damage_;
};

class Heal final : public InstantEffect {
public:
  Heal(int heal)
    : InstantEffect{ EffectType::Heal, School::Any }, heal_{ heal } {}

private:
  int strength_() const override { return heal_; }

  const int heal_;
};



class OverTimeEffect : public CardEffect {
public:
  const int strength;
  const int turns;

protected:
  OverTimeEffect(int strength, int turns, EffectType type, School school)
    : CardEffect{ type, school }, strength{ strength }, turns{ turns }
  {}
};

class DoT final : public OverTimeEffect {
public:
  DoT(int damage, int turns, School school)
    : OverTimeEffect{ damage, turns, EffectType::DoT, school } {}
  DoT(int damage, School school)
    : OverTimeEffect{ damage, 3, EffectType::DoT, school } {}
};

class HoT final : public OverTimeEffect {
public:
  HoT(int heal, int turns)
    : OverTimeEffect{ heal, turns, EffectType::HoT, School::Any } {}

  HoT(int heal)
    : OverTimeEffect{ heal, 3, EffectType::HoT, School::Any } {}
};



enum class HangingEffectDomain {
  Damage,
  Accuracy,
  Healing
};

std::ostream& operator<<(std::ostream& out, const HangingEffectDomain& t);

class Charm final : public CardEffect {
public:
  Charm(int strength, HangingEffectDomain domain, School school)
    : CardEffect{ EffectType::Charm, school },
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
