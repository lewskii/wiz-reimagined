#pragma once




namespace Effect {
  enum class Type {
    Damage,
    DoT,
    Heal,
    Charm
  };

  class Effect {
  public:
    virtual ~Effect() = default;

    const Type type;

  protected:
    Effect(Type t) : type{ t } {}
  };


  class Instant : public Effect {
  public:
    int strength() { return strength_(); }

  protected:
    Instant(Type t) : Effect{ t } {}

    virtual int strength_() const = 0;
  };

  class VariableDamage final : public Instant {
  public:
    VariableDamage(int base, int step);
    VariableDamage(int base);

  private:
    int strength_() const override;

    const int base_;
    const int step_;
  };

  class FlatDamage final : public Instant {
  public:
    FlatDamage(int damage);

  private:
    int strength_() const override { return damage_; }

    const int damage_;
  };

  class Heal final : public Instant {
  public:
    Heal(int heal);

  private:
    int strength_() const override { return heal_; }

    const int heal_;
  };


  class OverTime : public Effect {
  public:
    const int strength;
    const int turns;

  protected:
    OverTime(int strength, int turns, Type type);
  };

  class DoT final : public OverTime {
  public:
    DoT(int damage, int turns);
    DoT(int damage);
  };


  class Charm : public Effect {
  public:
    const int strength;
  };

}

namespace HangingEffect {

  class OverTime {
  public:
    virtual ~OverTime() = default;

    const Effect::Type type;
    const int per_turn;
    int turns_left;

  protected:
    OverTime(const Effect::OverTime& base, Effect::Type type);
  };

  class DoT : public OverTime {
  public:
    DoT(const Effect::DoT& base);
  };

}
