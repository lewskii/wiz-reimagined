#pragma once




namespace Effect {
  enum class Type {
    Damage,
    DoT,
    Heal,
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
    virtual int strength() const = 0;
  protected:
    Instant(Type t) : Effect{ t } {}
  };

  class VariableDamage final : public Instant {
  public:
    VariableDamage(int base, int step);
    VariableDamage(int base);

    int strength() const override;

  private:
    const int base_;
    const int step_;
  };

  class FlatDamage final : public Instant {
  public:
    FlatDamage(int damage);

    int strength() const override { return damage_; }

  private:
    const int damage_;
  };

  class Heal final : public Instant {
  public:
    Heal(int heal);

    int strength() const override { return heal_; }

  private:
    const int heal_;
  };


  class OverTime : public Effect {
  public:
    OverTime(int strength, int turns, Type type);

    const int strength_;
    const int turns_;
  };

  class DoT final : public OverTime {
  public:
    DoT(int damage, int turns);
    DoT(int damage);
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
