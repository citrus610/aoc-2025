#include <bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;

enum Cell : i64 {
    START = -1,
    SPLIT = -2
};

std::vector<std::vector<i64>> get_input()
{
    std::vector<std::vector<i64>> result;

    auto file = std::ifstream("input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        result.emplace_back();

        for (auto c : line) {
            if (c == 'S') {
                result.back().push_back(Cell::START);
            }
            else if (c == '^') {
                result.back().push_back(Cell::SPLIT);
            }
            else {
                result.back().push_back(0);
            }
        }
    }

    file.close();
    
    return result;
};

void part_1()
{
    auto input = get_input();

    u64 result = 0;

    for (int y = 1; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            auto& now = input[y][x];
            auto& old = input[y - 1][x];

            if (old != Cell::START && old < 1) {
                continue;
            }

            if (now == 0) {
                now = 1;
                continue;
            }

            if (now == Cell::SPLIT) {
                if (x > 0 && input[y][x - 1] == 0) {
                    input[y][x - 1] = 1;
                }

                if (x < input[y].size() - 1 && input[y][x + 1] == 0) {
                    input[y][x + 1] = 1;
                }

                result += 1;
            }
        }
    }

    std::cout << result << std::endl;
};

void part_2()
{
    auto input = get_input();

    u64 result = 0;

    for (int y = 1; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            auto& now = input[y][x];
            auto& old = input[y - 1][x];

            if (old != Cell::START && old < 1) {
                continue;
            }

            if (now >= 0) {
                now = old == Cell::START ? 1 : now + old;
                continue;
            }

            if (now == Cell::SPLIT) {
                if (x > 0 && input[y][x - 1] >= 0) {
                    input[y][x - 1] += old;
                }

                if (x < input[y].size() - 1 && input[y][x + 1] >= 0) {
                    input[y][x + 1] += old;
                }
            }
        }
    }

    for (auto& value : input.back()) {
        result += value;
    }

    std::cout << result << std::endl;
};

int main()
{
    part_1();
    part_2();

    return 0;
};