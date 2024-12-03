//
// Created by Lucas on 03-12-2024.
//

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <chrono>

int main() {
    std::ifstream file("..\\Day 3\\input.txt");
    auto start = std::chrono::high_resolution_clock::now();
    std::stringstream ss;
    while (file >> ss.rdbuf());

    std::string s = ss.str();
    std::vector<std::string> multiplies;
    int index;
    std::regex regex(R"(mul\(\d+,\d+\))");
    std::smatch match;
    while (std::regex_search(s, match, regex)) {
        multiplies.push_back(match.str());
        s.erase(0, s.find(match.str()) + match.str().size());
    }
    int total = 0;
    for (const auto& mul: multiplies) {
        auto commaIndex = mul.find(",");
        auto first = std::stoi(mul.substr(4, commaIndex - 4));
        auto second = std::stoi(mul.substr(commaIndex + 1, mul.find(")") - (commaIndex + 1)));
        auto result = first * second;
        std::cout << mul << " has " << first << " and " << second << " multiplies to: " << result << std::endl;
        total += result;
    }
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << "Total: " << total << " Time: " << duration << " ms" << std::endl;
    return 0;
}