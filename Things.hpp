#pragma once
#include "Inventory.hpp"

class Things : public InventoryItem {
 public:
  Things(int id, const std::string& name) : InventoryItem(id, name) {}
};

class Helmet : public Things {
 public:
  Helmet(int id, const std::string& name) : Things(id, name) {}

  void print(std::ostream& os) const override {
    os << "Helmet " << name << " (" << id << ")";
  }
};

class Dock : public Things, public EnergyConsumer {
  double energy;

 public:
  Dock(int id, const std::string& name, double energy)
      : Things(id, name), energy(energy) {}

  double dailyEnergy() override { return energy; }

  void print(std::ostream& os) const override {
    os << "Dock " << name << " (" << id << ")";
  }
};