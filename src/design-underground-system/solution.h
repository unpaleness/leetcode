#include <string>
#include <unordered_map>
#include <unordered_set>

struct NamePair {
    std::string first {};
    std::string second {};
};

template <>
struct std::hash<NamePair> {
    std::size_t operator()(NamePair const& namePair) const noexcept
    {
        const auto h1 = std::hash<std::string> {}(namePair.first);
        const auto h2 = std::hash<std::string> {}(namePair.second);
        return h1 ^ (h2 << 1);
    }
};

template <>
struct std::equal_to<NamePair> {
    bool operator()(const NamePair& lhs, const NamePair& rhs) const
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

struct AverageTime {
    double value { 0.f };
    int counter { 0 };
};

struct Customer {
    std::string startStation {};
    int time { 0 };
};

class UndergroundSystem {
public:
    UndergroundSystem() { }

    void checkIn(int id, std::string stationName, int t)
    {

        checkedInCustomers.insert_or_assign(id, Customer { stationName, t });
    }

    void checkOut(int id, std::string stationName, int t)
    {
        const auto customerIt = checkedInCustomers.find(id);
        if (customerIt == checkedInCustomers.end()) {
            return;
        }
        const auto newTime = static_cast<double>(t - customerIt->second.time);
        const auto averageTravelTimeIt = averageTravelTime.find({ customerIt->second.startStation, stationName });
        if (averageTravelTimeIt == averageTravelTime.end()) {
            averageTravelTime.emplace(NamePair { customerIt->second.startStation, stationName }, AverageTime { newTime, 1 });
        } else {
            const auto counter = averageTravelTimeIt->second.counter;
            const auto prevValue = averageTravelTimeIt->second.value;
            averageTravelTimeIt->second.value = (prevValue * counter + newTime) / (counter + 1);
            ++averageTravelTimeIt->second.counter;
        }
    }

    double getAverageTime(std::string startStation, std::string endStation)
    {
        const auto averageTravelTimeIt = averageTravelTime.find({ startStation, endStation });
        if (averageTravelTimeIt != averageTravelTime.end()) {
            return averageTravelTimeIt->second.value;
        }
        return 0.f;
    }

private:
    std::unordered_map<int, Customer> checkedInCustomers;
    std::unordered_map<NamePair, AverageTime> averageTravelTime;
};
