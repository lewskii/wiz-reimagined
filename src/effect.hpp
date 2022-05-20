#pragma once




namespace Effect {
  enum class Type {
    Damage,
    Heal,
  };

  class Effect {
  public:
    virtual ~Effect() = default;

    virtual int strength() const { return 0; }

    const Type type;

  protected:
    Effect(Type t) : type{ t }
    {}
  };

  class VariableDamage final : public Effect {
  public:
    VariableDamage(int base, int increment);
    VariableDamage(int base);

    int strength() const override;

  private:
    const int base_;
    const int increment_;
  };

  class Heal final : public Effect {
  public:
    Heal(int heal);

    int strength() const override { return heal_;  }

  private:
    const int heal_;
  };

}
