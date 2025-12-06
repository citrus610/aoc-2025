#include <bits/stdc++.h>

using u64 = uint64_t;

enum class Operator
{
    ADD,
    MUL
};

struct Input
{
    std::vector<std::vector<u64>> numbers;
    std::vector<Operator> operators;
};

Input get_input_1()
{
    Input result;

    auto file = std::ifstream("input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        bool is_last_line = line.front() == '+' || line.front() == '*';

        if (!is_last_line) {
            result.numbers.emplace_back();
        }

        std::stringstream ss(line);
        std::string token;

        while (ss >> token) {
            if (is_last_line) {
                result.operators.push_back(token == "+" ? Operator::ADD : Operator::MUL);
            }
            else {
                result.numbers.back().push_back(std::stoull(token));
            }
        }
    }

    file.close();
    
    return result;
};

void part_1()
{
    auto input = get_input_1();

    u64 result = 0;

    for (u64 i = 0; i < input.operators.size(); i++) {
        auto op = input.operators[i];
        auto value = input.numbers.front()[i];

        for (u64 k = 1; k < input.numbers.size(); k++) {
            auto next = input.numbers[k][i];

            if (op == Operator::ADD) {
                value += next;
            }
            else if (op == Operator::MUL) {
                value *= next;
            }
        }

        result += value;
    }

    std::cout << result << std::endl;
};

bool is_empty_column(const std::vector<std::string>& lines, u64 index) {
    for (auto& line : lines) {
        if (line[index] != ' ') {
            return false;
        }
    }

    return true;
}

Input get_input_2()
{
    Input result;

    auto file = std::ifstream("input.txt");

    std::string line;

    std::vector<std::string> lines;

    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    result.numbers.emplace_back();

    for (u64 i = 0; i < lines.front().size(); i++) {
        if (is_empty_column(lines, i)) {
            result.numbers.emplace_back();
            continue;
        }

        u64 num = 0;

        for (u64 k = 0; k < lines.size(); k++) {
            auto c = lines[k][i];

            if (c == ' ') {
                continue;
            }

            if (c == '+' || c == '*') {
                result.operators.push_back(c == '+' ? Operator::ADD : Operator::MUL);
                continue;
            }

            if (num == 0) {
                num = c - '0';
            }
            else {
                num *= 10;
                num += c - '0';
            }
        }

        result.numbers.back().push_back(num);
    }

    file.close();
    
    return result;
};

void part_2()
{
    auto input = get_input_2();

    u64 result = 0;

    for (u64 i = 0; i < input.operators.size(); i++) {
        auto op = input.operators[i];
        auto value = input.numbers[i].front();

        for (u64 k = 1; k < input.numbers[i].size(); k++) {
            auto next = input.numbers[i][k];

            if (op == Operator::ADD) {
                value += next;
            }
            else if (op == Operator::MUL) {
                value *= next;
            }
        }

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