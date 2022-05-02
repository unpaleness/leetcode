#include <iostream>

#include "solution.h"

int main()
{
    auto* undergroundSystem = new UndergroundSystem();

    undergroundSystem->checkIn(45, "Leyton", 3);
    undergroundSystem->checkIn(32, "Paradise", 8);
    undergroundSystem->checkIn(27, "Leyton", 10);
    undergroundSystem->checkOut(45, "Waterloo", 15); // Customer 45 "Leyton" -> "Waterloo" in 15-3 = 12
    undergroundSystem->checkOut(27, "Waterloo", 20); // Customer 27 "Leyton" -> "Waterloo" in 20-10 = 10
    undergroundSystem->checkOut(32, "Cambridge", 22); // Customer 32 "Paradise" -> "Cambridge" in 22-8 = 14
    const auto avg1 = undergroundSystem->getAverageTime("Paradise", "Cambridge"); // return 14.00000. One trip "Paradise" -> "Cambridge", (14) / 1 = 14
    const auto avg2 = undergroundSystem->getAverageTime("Leyton", "Waterloo"); // return 11.00000. Two trips "Leyton" -> "Waterloo", (10 + 12) / 2 = 11
    undergroundSystem->checkIn(10, "Leyton", 24);
    const auto avg3 = undergroundSystem->getAverageTime("Leyton", "Waterloo"); // return 11.00000
    undergroundSystem->checkOut(10, "Waterloo", 38); // Customer 10 "Leyton" -> "Waterloo" in 38-24 = 14
    const auto avg4 = undergroundSystem->getAverageTime("Leyton", "Waterloo"); // return 12.00000. Three trips "Leyton" -> "Waterloo", (10 + 12 + 14) / 3 = 12

    std::cout << avg1 << '\n';
    std::cout << avg2 << '\n';
    std::cout << avg3 << '\n';
    std::cout << avg4 << '\n';

    delete undergroundSystem;

    return 0;
}
