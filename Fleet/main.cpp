#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Errors.hpp"
#include "Inventory.hpp"
#include "Registry.hpp"
#include "ServiceCenter.hpp"
#include "Things.hpp"
#include "Transport.hpp"

class Fleet {
 private:
  std::vector<std::shared_ptr<InventoryItem>> items;
  std::weak_ptr<InventoryItem> focusItem;

 public:
  void addItem(std::shared_ptr<InventoryItem> item) { items.push_back(item); }

  void printEnergy() {
    double total = 0;
    std::vector<double> parts;

    for (const auto& item : items) {
      if (auto consumer = dynamic_cast<EnergyConsumer*>(item.get())) {
        parts.push_back(consumer->dailyEnergy());
        total += consumer->dailyEnergy();
      }
    }

    for (int i = 0; i < (int)parts.size(); ++i) {
      std::cout << parts[i];
      if (i < (int)parts.size() - 1) std::cout << " + ";
    }
    std::cout << " = " << total << std::endl;
  }

  void printNovice() {
    for (const auto& item : items) {
      if (auto transport = dynamic_cast<Transport*>(item.get())) {
        if (transport->getScore() >= 6) {
          std::cout << transport->getName() << " " << transport->getId()
                    << std::endl;
        }
      }
    }
  }

  void printList() {
    std::vector<std::shared_ptr<InventoryItem>> sorted = items;
    std::sort(sorted.begin(), sorted.end(),
              [](const std::shared_ptr<InventoryItem>& a,
                 const std::shared_ptr<InventoryItem>& b) { return *a < *b; });

    for (const auto& item : sorted) {
      std::cout << *item << std::endl;
    }
  }

  void setFocus(int id) {
    for (const auto& item : items) {
      if (item->getId() == id) {
        focusItem = item;
        return;
      }
    }
    throw CommandError("Position not found");
  }

  void showFocus() {
    if (auto shared = focusItem.lock()) {
      std::cout << "focus: " << *shared << std::endl;
    } else {
      std::cout << "removed" << std::endl;
    }
  }

  void removeItem(int id) {
    auto it = std::remove_if(items.begin(), items.end(),
                             [id](const std::shared_ptr<InventoryItem>& item) {
                               return item->getId() == id;
                             });
    if (it != items.end()) {
      items.erase(it, items.end());
    }
  }

  void printMaxEnergy() {
    double maxE = -1.0;
    std::string maxName = "none";
    for (const auto& item : items) {
      if (auto consumer = dynamic_cast<EnergyConsumer*>(item.get())) {
        if (consumer->dailyEnergy() > maxE) {
          maxE = consumer->dailyEnergy();
          maxName = item->getName();
        }
      }
    }
    if (maxE >= 0) {
      std::cout << "max_energy: " << maxName << " (" << maxE << ")"
                << std::endl;
    } else {
      std::cout << "max_energy: none" << std::endl;
    }
  }

  void printCountNovice() {
    int count = 0;
    for (const auto& item : items) {
      if (auto transport = dynamic_cast<Transport*>(item.get())) {
        if (transport->getScore() >= 6) count++;
      }
    }
    std::cout << "count_novice: " << count << std::endl;
  }
};

int main() {
  Fleet fleet;
  ServiceCenter center;
  Registry<std::string> systemLog;
  std::string command;

  while (std::cin >> command) {
    try {
      if (command == "quit") {
        break;
      } else if (command == "add") {
        std::string type;
        std::cin >> type;
        int id;
        std::cin >> id;
        std::string name;
        std::cin >> name;
        std::unique_ptr<InventoryItem> newItem = nullptr;

        if (type == "scooter") {
          double energy;
          int score;
          std::cin >> energy >> score;
          newItem = std::make_unique<ElectricScooter>(id, name, energy, score);
        } else if (type == "bike") {
          int score;
          std::cin >> score;
          newItem = std::make_unique<Bike>(id, name, score);
        } else if (type == "ebike") {
          double energy;
          int score;
          std::cin >> energy >> score;
          newItem = std::make_unique<ElectricBike>(id, name, energy, score);
        } else if (type == "helmet") {
          newItem = std::make_unique<Helmet>(id, name);
        } else if (type == "dock") {
          double energy;
          std::cin >> energy;
          newItem = std::make_unique<Dock>(id, name, energy);
        } else {
          throw CommandError("Unknown transport type");
        }

        auto inspected = center.inspect(std::move(newItem));
        fleet.addItem(std::shared_ptr<InventoryItem>(std::move(inspected)));
        systemLog.add("Added: " + name);
      } else if (command == "energy") {
        {
          fleet.printEnergy();
        }
      } else if (command == "novice") {
        {
          fleet.printNovice();
        }
      } else if (command == "list") {
        {
          fleet.printList();
        }
      } else if (command == "show_focus") {
        {
          fleet.showFocus();
        }
      } else if (command == "max_energy") {
        {
          fleet.printMaxEnergy();
        }
      } else if (command == "count_novice") {
        {
          fleet.printCountNovice();
        }
      } else if (command == "show_log") {
        {
          systemLog.printAll();
        }
      } else if (command == "focus") {
        int id;
        std::cin >> id;
        fleet.setFocus(id);
      } else if (command == "remove") {
        int id;
        std::cin >> id;
        fleet.removeItem(id);
      } else {
        throw CommandError("Unknown command");
      }
    } catch (const FleetError& e) {
      std::cout << e.what() << std::endl;
    } catch (const std::exception& e) {
      std::cout << "error: " << e.what() << std::endl;
    }
  }
  return 0;
}