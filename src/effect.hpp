#pragma once




namespace Effect {
  enum class Type {
    Damage,
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

  class Heal final : public Effect {
  public:
    Heal(int heal);

    int strength() const override { return heal_;  }

  private:
    const int heal_;
  };

}
