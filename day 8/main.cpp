#include <bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;

struct Coord
{
    i64 x;
    i64 y;
    i64 z;
};

struct Pair
{
    std::array<i64, 2> ids;
    i64 distance;
};

struct Circuit
{
    std::vector<i64> ids;
};

std::vector<Coord> get_input()
{
    std::vector<Coord> result;

    auto file = std::ifstream("input.txt");

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string x;
        std::string y;
        std::string z;

        std::getline(ss, x, ',');
        std::getline(ss, y, ',');
        std::getline(ss, z, ',');

        result.push_back(Coord {
            .x = std::stoll(x),
            .y = std::stoll(y),
            .z = std::stoll(z)
        });
    }

    file.close();
    
    return result;
};

std::vector<Pair> get_pairs(const std::vector<Coord>& coords)
{
    std::vector<Pair> result;

    for (i64 i = 0; i < coords.size() - 1; i++) {
        for (i64 k = i + 1; k < coords.size(); k++) {
            result.push_back(Pair {
                { i, k },
                (coords[i].x - coords[k].x) * (coords[i].x - coords[k].x) +
                (coords[i].y - coords[k].y) * (coords[i].y - coords[k].y) +
                (coords[i].z - coords[k].z) * (coords[i].z - coords[k].z)
            });
        }
    }

    if (!result.empty()) {
        std::stable_sort(
            result.begin(),
            result.end(),
            [&] (const Pair& a, const Pair& b) {
                return a.distance > b.distance;
            }
        );
    }

    return result;
};

bool is_in_circuit(const Circuit& circuit, i64 id)
{
    for (const auto& i : circuit.ids) {
        if (i == id) {
            return true;
        }
    }

    return false;
};

i64 get_circuit_index_if_existed(const std::vector<Circuit>& circuits, i64 id)
{
    for (i64 i = 0; i < circuits.size(); i++) {
        if (is_in_circuit(circuits[i], id)) {
            return i;
        }
    }

    return -1;
}

void part_1()
{
    auto input = get_input();
    auto pairs = get_pairs(input);

    u64 result = 0;

    std::vector<Circuit> circuits;

    for (i64 i = 0; i < 1000; i++)
    {
        auto best = pairs.back();
        pairs.pop_back();

        i64 circuit_index_1 = get_circuit_index_if_existed(circuits, best.ids[0]);
        i64 circuit_index_2 = get_circuit_index_if_existed(circuits, best.ids[1]);

        if (circuit_index_1 >= 0 && circuit_index_2 >= 0) {
            if (circuit_index_1 != circuit_index_2) {
                auto& circuit_1 = circuits[circuit_index_1];
                auto& circuit_2 = circuits[circuit_index_2];
    
                circuit_1.ids.insert(circuit_1.ids.end(), circuit_2.ids.begin(), circuit_2.ids.end());
    
                circuits.erase(circuits.begin() + circuit_index_2);
            }
        }

        if (circuit_index_1 < 0 && circuit_index_2 < 0) {
            circuits.push_back(Circuit {
                .ids = { best.ids[0], best.ids[1] }
            });
        }

        if (circuit_index_1 >= 0 && circuit_index_2 < 0) {
            circuits[circuit_index_1].ids.push_back(best.ids[1]);
        }

        if (circuit_index_2 >= 0 && circuit_index_1 < 0) {
            circuits[circuit_index_2].ids.push_back(best.ids[0]);
        }
    }

    std::stable_sort(
        circuits.begin(),
        circuits.end(),
        [&] (const Circuit& a, const Circuit& b) {
            return a.ids.size() > b.ids.size();
        }
    );

    result = circuits.front().ids.size();

    for (i64 i = 1; i < 3; ++i) {
        result *= circuits[i].ids.size();
    }

    std::cout << result << std::endl;
};

void part_2()
{
    auto input = get_input();
    auto pairs = get_pairs(input);

    u64 result = 0;
    
    std::vector<Circuit> circuits;
    Pair last;

    while (!pairs.empty())
    {
        auto best = pairs.back();
        pairs.pop_back();

        i64 circuit_index_1 = get_circuit_index_if_existed(circuits, best.ids[0]);
        i64 circuit_index_2 = get_circuit_index_if_existed(circuits, best.ids[1]);

        if (circuit_index_1 >= 0 && circuit_index_2 >= 0) {
            if (circuit_index_1 != circuit_index_2) {
                auto& circuit_1 = circuits[circuit_index_1];
                auto& circuit_2 = circuits[circuit_index_2];
    
                circuit_1.ids.insert(circuit_1.ids.end(), circuit_2.ids.begin(), circuit_2.ids.end());
    
                circuits.erase(circuits.begin() + circuit_index_2);
            }
        }

        if (circuit_index_1 < 0 && circuit_index_2 < 0) {
            circuits.push_back(Circuit {
                .ids = { best.ids[0], best.ids[1] }
            });
        }

        if (circuit_index_1 >= 0 && circuit_index_2 < 0) {
            circuits[circuit_index_1].ids.push_back(best.ids[1]);
        }

        if (circuit_index_2 >= 0 && circuit_index_1 < 0) {
            circuits[circuit_index_2].ids.push_back(best.ids[0]);
        }

        if (circuits.size() == 1 && circuits.front().ids.size() == input.size()) {
            last = best;
            break;
        }
    }

    result = input[last.ids[0]].x * input[last.ids[1]].x;

    std::cout << result << std::endl;
};

int main()
{
    part_1();
    part_2();

    return 0;
};