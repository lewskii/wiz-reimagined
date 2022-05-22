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

    virtual int strength() const = 0;

    const Type type;

  protected:
    Effect(Type t) : type{ t }
    {}
  };

  class VariableDamage final : public Effect {
  public:
    VariableDamage(int base, int step);
    VariableDamage(int base);

    int strength() const override;

  private:
    const int base_;
    const int step_;
  };

  class FlatDamage final : public Effect {
  public:
    FlatDamage(int damage);

    int strength() const override { return damage_; }

  private:
    const int damage_;
  };

  class OverTime : public Effect {
  public:
    OverTime(int strength, int turns, Type type);

    virtual int strength() const = 0;

    const int strength_;
    const int turns_;
  };

  class DoT final : public OverTime {
  public:
    DoT(int damage, int turns);
    DoT(int damage);

    int strength() const override { return strength_; }
  };

  class Heal final : public Effect {
  public:
    Heal(int heal);

    int strength() const override { return heal_;  }

  private:
    const int heal_;
  };


  class HangingOverTime {
  public:
    virtual ~HangingOverTime() = default;

    const Type type;
    const int per_turn;
    int turns_left;

  protected:
    HangingOverTime(const OverTime& base, Type type);
  };

  class HangingDoT : public HangingOverTime {
  public:
    HangingDoT(const DoT& base);
  };

}
