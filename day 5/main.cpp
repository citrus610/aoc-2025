#include <bits/stdc++.h>

using u64 = uint64_t;

struct Input
{
    std::vector<std::pair<u64, u64>> ranges;
    std::vector<u64> ingredients;
};

Input get_input()
{
    Input result;

    auto file = std::ifstream("input.txt");
    bool is_ingredients = false;

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line.front() == ' ') {
            is_ingredients = true;
            continue;
        }

        if (is_ingredients) {
            result.ingredients.push_back(std::stoull(line));
        }
        else {
            std::stringstream ss(line);

            std::string min;
            std::string max;

            std::getline(ss, min, '-');
            std::getline(ss, max, '-');

            result.ranges.push_back({
                std::stoull(min),
                std::stoull(max)
            });
        }
    }

    file.close();
    
    return result;
};

bool is_fresh(u64 ingredient, const std::vector<std::pair<u64, u64>>& ranges)
{
    for (auto& range : ranges) {
        if (ingredient >= range.first && ingredient <= range.second) {
            return true;
        }
    }

    return false;
};

void part_1()
{
    auto input = get_input();

    u64 result = 0;

    for (auto ingredient : input.ingredients) {
        if (is_fresh(ingredient, input.ranges)) {
            result += 1;
        }
    }

    std::cout << result << std::endl;
};

bool is_overlapping(std::pair<u64, u64>& a, std::pair<u64, u64>& b) {
    return a.second >= b.first && a.first <= b.second;
}

void part_2()
{
    auto input = get_input();

    u64 result = 0;

    while (true) {
        std::unordered_set<int> overlapped;

        for (int i = 0; i < input.ranges.size() - 1; i++) {
            for (int k = i + 1; k < input.ranges.size(); k++) {
                auto& current = input.ranges[i];
                auto& next = input.ranges[k];

                if (is_overlapping(current, next)) {
                    current.first = std::min(current.first, next.first);
                    current.second = std::max(current.second, next.second);

                    overlapped.insert(k);
                }
            }
        }

        if (overlapped.empty()) {
            break;
        }

        for (int i = input.ranges.size() - 1; i >= 0; i--) {
            if (overlapped.find(i) != overlapped.end()) {
                input.ranges.erase(input.ranges.begin() + i);
            }
        }
    }

    for (auto& r : input.ranges) {
        result += r.second - r.first + 1;
    }

    std::cout << result << std::endl;
};

int main()
{
    part_1();
    part_2();

    return 0;
};