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
            result.back().push_back(c == '.' ? 0 : 1);
        }
    }

    file.close();
    
    return result;
};

int get_count(const std::vector<std::vector<int>>& input, int x, int y)
{
    int count = 0;

    auto w = input.front().size();
    auto h = input.size();

    if (input[y][x] == 0) {
        return 100;
    }

    for (int dy = -1; dy < 2; dy++) {
        if (y + dy < 0 || y + dy >= h) {
            continue;
        }

        for (int dx = -1; dx < 2; dx++) {
            if (dx == 0 && dy == 0) {
                continue;
            }

            if (x + dx < 0 || x + dx >= w) {
                continue;
            }

            count += input[y + dy][x + dx];
        }
    }

    return count;
};

void part_1()
{
    auto input = get_input();
    auto w = input.front().size();
    auto h = input.size();

    u64 result = 0;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            result += get_count(input, x, y) < 4;
        }
    }

    std::cout << result << std::endl;
};

void part_2()
{
    auto input = get_input();
    auto w = input.front().size();
    auto h = input.size();

    u64 result = 0;

    while (true) {
        u64 count = 0;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (get_count(input, x, y) < 4) {
                    count += 1;
                    input[y][x] = 0;
                }
            }
        }

        result += count;

        if (count == 0) {
            break;
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