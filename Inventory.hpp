#pragma once
#include <iostream>
#include <string>

class InventoryItem {
 protected:
  int id;
  std::string name;

 public:
  InventoryItem(int id, const std::string& name) : id(id), name(name) {}
  virtual ~InventoryItem() = default;

  int getId() { return id; }
  std::string getName() { return name; }

  virtual void print(std::ostream& os) const = 0;

  bool operator<(const InventoryItem& other) const { return id < other.id; }

  friend std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
    item.print(os);
    return os;
  }
};

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;
  virtual double dailyEnergy() = 0;
};