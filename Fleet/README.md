Сервис ФизКат

Собирал на Windows через MSYS2.
В терминале VS Code пишем:
g++ -std=c++17 \*.cpp -o fleet
Запуск: .\fleet.exe

Разбил код на файлы main, Inventory, Transport, Things, ServiceCenter, Registry, Errors

Схема наследования
Базовый класс InventoryItem, от которого наследуется Transport и Things.
Есть отдельный интерфейс EnergyConsumer (виртуальный dailyEnergy), чтобы можно было отличать, кто использует энергию, а кто нет

Множественное наследование
ElectricScooter : Transport + EnergyConsumer
Dock : Things + EnergyConsumer
ElectricBike : Transport + EnergyConsumer

Умные указатели
unique_ptr - используется в ServiceCenter::inspect. Если в имени есть "broken", сервис кидает исключение и объект просто удаляется, не попадая в парк
shared_ptr - в Fleet. Вектор хранит shared_ptr<InventoryItem>
weak_ptr - для витрины. Если тачку удаляют из парка, lock() возвращает пусто и show_focus пишет "removed"

Исключения
Сделал иерархию от std::runtime_error: FleetError, InspectionError и CommandError
Весь ввод команд в main сделан через try-catch, поэтому если ввести что-то некорректно, программа напишет "error: ..."

Шаблоны
Шаблонный класс Registry<T>. Есть специализация для std::string, которая добавляет "[LOG]". Использую его в main, чтобы записывать успешно добавленную технику

Креатив
Добавил класс ElectricBike и команду add ebike.
Добавил две команды:
max_energy: ищет самый прожорливый прибор в парке
count_novice: считает, сколько у нас техники для новичков

ИИ
Использовал ии, чтобы правильно передать unique_ptr в функцию через std::move и понять, зачем нужен lock() у weak_ptr
Спрашивал, почему компилятор ругается на повторное определение классов. Оказалось в начале нужен #pragma once
Помогал со сборкой и запуском
