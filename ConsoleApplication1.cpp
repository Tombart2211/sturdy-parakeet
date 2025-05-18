#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>;

// Структура для представлення IoT-пристрою
struct Device {
    std::string name;
    double powerConsumption; // Поточне споживання енергії (Вт)
    bool status;             // Стан пристрою (вкл/викл)
};

// Функція для генерації випадкового споживання енергії
double getRandomPowerUsage() {
    return (rand() % 500 + 100) / 10.0; // Випадкове значення від 10.0 до 60.0 Вт
}

// Функція для виведення стану пристроїв
void displayDevices(const std::vector<Device>& devices) {
    std::cout << "\nСтан пристроїв у системі:\n";
    for (const auto& device : devices) {
        std::cout << "Пристрій: " << device.name
            << " | Споживання: " << device.powerConsumption << " Вт"
            << " | Статус: " << (device.status ? "Увімкнено" : "Вимкнено") << "\n";
    }
}

// Функція для розрахунку загального енергоспоживання
double calculateTotalConsumption(const std::vector<Device>& devices) {
    double total = 0;
    for (const auto& device : devices) {
        if (device.status) {
            total += device.powerConsumption;
        }
    }
    return total;
}

// Функція для імітації надсилання даних у хмарний сервіс
void sendDataToCloud(double totalConsumption) {
    std::cout << "\n[Cloud] Надсилання даних: Загальне споживання енергії = " << totalConsumption << " Вт\n";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));

    std::vector<Device> devices = {
        {"Освітлення", getRandomPowerUsage(), true},
        {"Кондиціонер", getRandomPowerUsage(), true},
        {"Телевізор", getRandomPowerUsage(), false},
        {"Холодильник", getRandomPowerUsage(), true},
        {"Бойлер", getRandomPowerUsage(), false}
    };

    while (true) {
        displayDevices(devices);
        double totalConsumption = calculateTotalConsumption(devices);
        std::cout << "Загальне споживання енергії: " << totalConsumption << " Вт\n";

        sendDataToCloud(totalConsumption);

        std::cout << "\nОновити дані? (1 - Так, 0 - Вийти): ";
        int choice;
        std::cin >> choice;
        if (choice == 0) break;

        // Оновлення випадкового пристрою
        int deviceIndex = rand() % devices.size();
        devices[deviceIndex].powerConsumption = getRandomPowerUsage();
        devices[deviceIndex].status = rand() % 2;
    }

    return 0;
}
