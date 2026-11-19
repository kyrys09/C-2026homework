#pragma once
#include <memory>
#include <string>

#include "Errors.hpp"
#include "Inventory.hpp"

class ServiceCenter {
 public:
  std::unique_ptr<InventoryItem> inspect(std::unique_ptr<InventoryItem> item) {
    if (item->getName().find("broken") != std::string::npos) {
      throw InspectionError("error: inspection rejected");
    }
    return item;
  }
};