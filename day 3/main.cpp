#include <bits/stdc++.h>

using u64 = uint64_t;

std::vector<std::vector<int>> get_input()
{
    std::vector<std::vector<int>> result;

    auto file = std::ifstream("input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        result.emplace_back();

        for (auto c : line) {
            result.back().push_back(c - 48);
        }
    }

    file.close();
    
    return result;
};

void part_1()
{
    auto input = get_input();

    u64 result = 0;

    for (auto& line : input) {
        auto iter_1st = std::max_element(line.begin(), line.end() - 1);
        auto iter_2nd = std::max_element(iter_1st + 1, line.end());

        result += *iter_1st * 10 + *iter_2nd;
    }

    std::cout << result << std::endl;
};

void part_2()
{
    auto input = get_input();

    u64 result = 0;

    for (auto& line : input) {
        auto iter = line.begin();

        for (int i = 0; i < 12; i++) {
            auto next = std::max_element(iter, line.end() - 11 + i);
            iter = next + 1;
            result += *next * std::pow(10, 11 - i);
        }
    }

    std::cout << result << std::endl;
};

int main()
{
    part_1();
    part_2();

    return 0;
};