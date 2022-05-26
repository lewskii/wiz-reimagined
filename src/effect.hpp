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
  VariableDamage(int base, int step);
  VariableDamage(int base);

private:
  int strength_() const override;

  const int base_;
  const int step_;
};

class FlatDamage final : public InstantEffect {
public:
  FlatDamage(int damage);

private:
  int strength_() const override { return damage_; }

  const int damage_;
};

class Heal final : public InstantEffect {
public:
  Heal(int heal);

private:
  int strength_() const override { return heal_; }

  const int heal_;
};



class OverTimeEffect : public CardEffect {
public:
  const int strength;
  const int turns;

protected:
  OverTimeEffect(int strength, int turns, EffectType type);
};

class DoT final : public OverTimeEffect {
public:
  DoT(int damage, int turns);
  DoT(int damage);
};

class HoT final : public OverTimeEffect {
public:
  HoT(int heal, int turns);
  HoT(int heal);
};



enum class CharmType {
  Damage,
  Accuracy,
  Heal
};

class HangingEffect : public CardEffect {
public:
  const int strength;
  const CharmType type;

protected:
  HangingEffect(int strength, CharmType type);
};

class Charm final : public HangingEffect {
public:
  Charm(int strength, CharmType type) : HangingEffect{ strength, type } {}
};




class HangingOverTime {
public:
  virtual ~HangingOverTime() = default;

  const EffectType type;
  const int per_turn;
  int turns_left;

protected:
  HangingOverTime(const OverTimeEffect& base, EffectType type);
};

class HangingDoT : public HangingOverTime {
public:
  HangingDoT(const DoT& base);
};

class HangingHoT : public HangingOverTime {
public:
  HangingHoT(const HoT& base);
};
