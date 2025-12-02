#include <bits/stdc++.h>

using u64 = uint64_t;

std::vector<std::pair<u64, u64>> get_input()
{
    std::vector<std::pair<u64, u64>> result;

    auto file = std::ifstream("input.txt");

    std::string line;

    while (std::getline(file, line, ','))
    {
        std::stringstream ss(line);

        std::string num_1;
        std::string num_2;

        std::getline(ss, num_1, '-');
        std::getline(ss, num_2, '-');

        result.push_back({
            std::stoull(num_1),
            std::stoull(num_2)
        });
    }

    file.close();
    
    return result;
};

void part_1()
{
    auto input = get_input();

    u64 result = 0;

    for (auto& pair : input) {
        for (u64 i = pair.first; i <= pair.second; ++i) {
            auto size = std::to_string(i).size();

            if ((size % 2) != 0) {
                i = std::pow(10, size);
                continue;
            }

            u64 magic = std::pow(10, size / 2) + 1;

            if ((i % magic) == 0) {
                result += i;
            }
        }
    }

    std::cout << result << std::endl;
};

void part_2()
{
    auto input = get_input();

    u64 result = 0;

    for (auto& pair : input) {
        for (u64 i = pair.first; i <= pair.second; ++i) {
            auto size = std::to_string(i).size();

            for (u64 k = 2; k <= size; ++k) {
                if ((size % k) != 0) {
                    continue;
                }

                u64 magic = 1;

                for (u64 j = 1; j < k; ++j) {
                    magic += std::pow(10, size / k * j);
                }
    
                if ((i % magic) == 0) {
                    result += i;
                    break;
                }
            }
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