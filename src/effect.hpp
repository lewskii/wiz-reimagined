#pragma once




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

protected:
  CardEffect(EffectType t) : type{ t } {}
};


class InstantEffect : public CardEffect {
public:
  int strength() { return strength_(); }

protected:
  InstantEffect(EffectType t) : CardEffect{ t } {}

  virtual int strength_() const = 0;
};

class VariableDamage final : public InstantEffect {
public:
  VariableDamage(int base, int step)
    : InstantEffect{ EffectType::Damage }, base_{ base }, step_{ step } {}
  VariableDamage(int base)
    : InstantEffect{ EffectType::Damage },  base_{ base }, step_{ 10 } {}

private:
  int strength_() const override;

  const int base_;
  const int step_;
};

class FlatDamage final : public InstantEffect {
public:
  FlatDamage(int damage)
    : InstantEffect{ EffectType::Damage }, damage_{ damage } {}

private:
  int strength_() const override { return damage_; }

  const int damage_;
};

class Heal final : public InstantEffect {
public:
  Heal(int heal) : InstantEffect{ EffectType::Heal }, heal_{ heal } {}

private:
  int strength_() const override { return heal_; }

  const int heal_;
};



class OverTimeEffect : public CardEffect {
public:
  const int strength;
  const int turns;

protected:
  OverTimeEffect(int strength, int turns, EffectType type)
    : CardEffect{ type }, strength{ strength }, turns{ turns }
  {}
};

class DoT final : public OverTimeEffect {
public:
  DoT(int damage, int turns)
    : OverTimeEffect{ damage, turns, EffectType::DoT } {}
  DoT(int damage)
    : OverTimeEffect{ damage, 3, EffectType::DoT } {}
};

class HoT final : public OverTimeEffect {
public:
  HoT(int heal, int turns) : OverTimeEffect{ heal, turns, EffectType::HoT } {}

  HoT(int heal) : OverTimeEffect{ heal, 3, EffectType::HoT } {}
};



enum class HangingEffectDomain {
  Damage,
  Accuracy,
  Heal
};

std::ostream& operator<<(std::ostream& out, const HangingEffectDomain& t);

class Charm final : public CardEffect {
public:
  Charm(int strength, HangingEffectDomain domain)
    : CardEffect{ EffectType::Charm }, strength{ strength }, domain{ domain } {}

  const int strength;
  const HangingEffectDomain domain;
};


class HangingEffect {
public:
  const EffectType type;
  const int strength;
  const HangingEffectDomain domain;

protected:
  HangingEffect(EffectType type, int strength, HangingEffectDomain domain)
    : type{ type }, strength{ strength }, domain{ domain } {}
};

class HangingCharm final : public HangingEffect {
public:
  HangingCharm(Charm c)
    : HangingEffect{ EffectType::Charm, c.strength, c.domain } {}
};




class HangingOverTime {
public:
  virtual ~HangingOverTime() = default;

  const EffectType type;
  const int per_turn;
  int turns_left;

protected:
  HangingOverTime(const OverTimeEffect& base, EffectType type)
    : type{ type },
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
