#include <bits/stdc++.h>

std::vector<int> get_input()
{
    std::vector<int> result;

    auto file = std::ifstream("input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        bool positive = true;

        if (line.front() == 'L') {
            positive = false;
        }

        line.erase(line.begin());

        int value = std::stoi(line);

        if (!positive) {
            value = -value;
        }

        result.push_back(value);
    }

    file.close();
    
    return result;
};

void part_1()
{
    std::vector<int> input = get_input();

    int value = 50;
    int result = 0;

    for (int step : input) {
        value = (value + step) % 100;
    
        if (value == 0) {
            result += 1;
        }
    }

    std::cout << result << std::endl;
};

void part_2()
{
    std::vector<int> input = get_input();

    int value = 50;
    int result = 0;

    for (int step : input) {
        int sign = step < 0 ? -1 : 1;

        for (int i = 0; i < abs(step); ++i) {
            value += sign;

            if (value < 0) {
                value += 100;
            }

            if (value >= 100) {
                value -= 100;
            }

            if (value == 0) {
                result += 1;
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