#pragma once
#include "Inventory.hpp"

class Transport : public InventoryItem {
 protected:
  int score;

 public:
  Transport(int id, const std::string& name, int score)
      : InventoryItem(id, name), score(score) {}

  int getScore() { return score; }
};

class Scooter : public Transport {
 public:
  Scooter(int id, const std::string& name, int score)
      : Transport(id, name, score) {}

  void print(std::ostream& os) const override {
    os << "Scooter " << name << " (" << id << ")";
  }
};

class Bike : public Transport {
 public:
  Bike(int id, const std::string& name, int score)
      : Transport(id, name, score) {}

  void print(std::ostream& os) const override {
    os << "Bike " << name << " (" << id << ")";
  }
};

class ElectricScooter : public Transport, public EnergyConsumer {
  double energy;

 public:
  ElectricScooter(int id, const std::string& name, double energy, int score)
      : Transport(id, name, score), energy(energy) {}

  double dailyEnergy() override { return energy; }

  void print(std::ostream& os) const override {
    os << "ElectricScooter " << name << " (" << id << ")";
  }
};

class ElectricBike : public Transport, public EnergyConsumer {
  double energy;

 public:
  ElectricBike(int id, const std::string& name, double energy, int score)
      : Transport(id, name, score), energy(energy) {}

  double dailyEnergy() override { return energy; }

  void print(std::ostream& os) const override {
    os << "ElectricBike " << name << " (" << id << ")";
  }
};